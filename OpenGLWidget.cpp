#include "OpenGLWidget.h"

#include "GraphicsObject.h"
#include "OpenGLInterface.h"
#include "ShaderProgram.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget{parent}
{
  constexpr int32_t NUMBER_OF_SAMPLES = 4;

  setFocusPolicy(Qt::StrongFocus);

  QSurfaceFormat format = QOpenGLWidget::format();
  format.setVersion(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setSamples(NUMBER_OF_SAMPLES);
  setFormat(format);

  constexpr float pi = 3.14159265358979323846f;
  Point4f color{0.0f, 0.0f, 0.0f, 1.0f};
  for (float x = 0.0; x < pi; x += 0.031415927) {
    color[0] = std::sin(x);
    color[1] = std::abs(std::cos(x));
    highlight_colors_.push_back(color);
  }
}

void OpenGLWidget::update_graphics_object()
{
  graphics_object_->set_highlight_color(highlight_colors_[highlight_color_index_]);
  ++highlight_color_index_;
  highlight_color_index_ %= highlight_colors_.size();

  update();
}

void OpenGLWidget::initializeGL()
{
  OpenGLInterface::set_api(context()->versionFunctions<OpenGLInterface::OpenGLFunctions>());
  auto gl_funcs = OpenGLInterface::get_api();
  if (!gl_funcs) {
    // Resolving Open GL API failed, cann
    throw std::runtime_error("Resolving Open GL functions failed.");
  }

  std::cout << "GL_VENDOR: " << gl_funcs->glGetString(GL_VENDOR) << "\n";
  std::cout << "GL_RENDERER: " << gl_funcs->glGetString(GL_RENDERER) << "\n";
  std::cout << "GL_VERSION: " << gl_funcs->glGetString(GL_VERSION) << "\n";
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << gl_funcs->glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

  gl_funcs->glEnable(GL_MULTISAMPLE);

  gl_funcs->glEnable(GL_DEPTH_TEST);
  gl_funcs->glDepthFunc(GL_LEQUAL);

  gl_funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  load_shaders();

  graphics_object_ = std::unique_ptr<GraphicsObject>{new GraphicsObject{"model.bin"}};
}

void OpenGLWidget::resizeGL(int width, int height)
{
  if (width_ == width && height_ == height)
    return;

  width_ = width;
  height_ = height;

  constexpr double FOVY = 60.0;
  constexpr double NEAR = 1.0;
  constexpr double FAR = 100.0;

  double aspect_ratio = static_cast<double>(width_) / static_cast<double>(height_);

  projection_matrix_.setZero();

  double q = 1.0 / std::tan(0.5 * FOVY * 3.141592653589793 / 180.0);
  projection_matrix_(0, 0) = q / aspect_ratio;
  projection_matrix_(1, 1) = q;
  projection_matrix_(2, 2) = (NEAR + FAR) / (NEAR - FAR);
  projection_matrix_(2, 3) = -1.0;
  projection_matrix_(3, 2) = (2.0 * NEAR * FAR) / (NEAR - FAR);

  OpenGLInterface::get_api()->glViewport(0, 0, width_, height_);
}

void OpenGLWidget::paintGL()
{
  auto gl_funcs = OpenGLInterface::get_api();

  gl_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl_funcs->glUseProgram(shader_program_->get_program_id());
  shader_program_->set_matrix("projection_matrix", projection_matrix_);
  shader_program_->set_matrix("model_view_matrix", viewpoint_camera_.get_view_matrix());
  graphics_object_->render(shader_program_);

  gl_funcs->glUseProgram(shader_program2_->get_program_id());
  shader_program2_->set_matrix("projection_matrix", projection_matrix_);
  shader_program2_->set_matrix("model_view_matrix", viewpoint_camera_.get_view_matrix());
  graphics_object_->render_highlight(shader_program2_);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* mouse_event)
{
  Point2i mouse_position{mouse_event->x(), mouse_event->y()};

  Point2d start_pos = normalize(previous_mouse_position_);
  Point2d end_pos = normalize(mouse_position);

  viewpoint_camera_.rotate(start_pos, end_pos);

  previous_mouse_position_ = mouse_position;
}

void OpenGLWidget::mousePressEvent(QMouseEvent* mouse_event)
{
  previous_mouse_position_ = Point2i{mouse_event->x(), mouse_event->y()};
}

void OpenGLWidget::wheelEvent(QWheelEvent* wheel_event)
{
  viewpoint_camera_.zoom(wheel_event->delta() / 100);
}

void OpenGLWidget::load_shaders()
{
  {
    shader_program_ = std::unique_ptr<ShaderProgram>{new ShaderProgram{}};

    Shader vertex_shader{GL_VERTEX_SHADER};
    vertex_shader.compile("bv.vert");
    shader_program_->attach_shader(std::move(vertex_shader));

    Shader fragement_shader{GL_FRAGMENT_SHADER};
    fragement_shader.compile("bv.frag");
    shader_program_->attach_shader(std::move(fragement_shader));

    shader_program_->link();
  }

  // highlight shader
  {
    shader_program2_ = std::unique_ptr<ShaderProgram>{new ShaderProgram{}};

    Shader vertex_shader{GL_VERTEX_SHADER};
    vertex_shader.compile("bv2.vert");
    shader_program2_->attach_shader(std::move(vertex_shader));

    Shader fragement_shader{GL_FRAGMENT_SHADER};
    fragement_shader.compile("bv2.frag");
    shader_program2_->attach_shader(std::move(fragement_shader));

    shader_program2_->link();
  }
}

Point2d OpenGLWidget::normalize(const Point2i& position)
{
  return Point2d{(2.0 * position.x() - width_) / static_cast<double>(width_),
                 (height_ - 2.0 * position.y()) / static_cast<double>(height_)};
}
