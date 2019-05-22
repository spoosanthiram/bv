#include "OpenGLWidget.h"

#include "OpenGLInterface.h"

#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget* parent)
  : QOpenGLWidget{parent}
{
  constexpr int32_t NUMBER_OF_SAMPLES = 4;

  setFocusPolicy(Qt::StrongFocus);

  QSurfaceFormat format = QOpenGLWidget::format();
  format.setVersion(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setSamples(NUMBER_OF_SAMPLES);
  setFormat(format);
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
}

void OpenGLWidget::resizeGL(int width, int height)
{
  if (width_ == width && height_ == height)
    return;

  width_ = width;
  height_ = height;

  OpenGLInterface::get_api()->glViewport(0, 0, width_, height_);
}

void OpenGLWidget::paintGL()
{
  OpenGLInterface::get_api()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidget::load_shaders()
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
