#pragma once

#include "GeometryTypes.h"
#include "ViewpointCamera.h"

#include <Eigen/Core>
#include <QOpenGLWidget>

#include <memory>
#include <vector>

class GraphicsObject;
class ShaderProgram;

class OpenGLWidget : public QOpenGLWidget
{
public:
  OpenGLWidget(QWidget* parent);
  ~OpenGLWidget() = default;

  void update_graphics_object();

protected:
  /// @brief Overrides of QOpenGLWidget
  /// @{
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void mouseMoveEvent(QMouseEvent* mouse_event) override;
  void mousePressEvent(QMouseEvent* mouse_event) override;
  void wheelEvent(QWheelEvent* wheel_event) override;
  /// @}

private:
  void load_shaders();
  Point2d normalize(const Point2i& position);

private:
  int32_t width_;
  int32_t height_;

  std::unique_ptr<ShaderProgram> shader_program_;
  std::unique_ptr<ShaderProgram> shader_program2_;
  Eigen::Matrix4d projection_matrix_;
  ViewpointCamera viewpoint_camera_;
  std::unique_ptr<GraphicsObject> graphics_object_;

  Point2i previous_mouse_position_{0, 0};

  std::vector<Point4f> highlight_colors_;
  size_t highlight_color_index_{0};
};
