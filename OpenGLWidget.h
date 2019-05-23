#pragma once

#include "ViewpointCamera.h"

#include <Eigen/Core>
#include <QOpenGLWidget>

#include <memory>

class GraphicsObject;
class ShaderProgram;

class OpenGLWidget : public QOpenGLWidget
{
public:
  OpenGLWidget(QWidget* parent);
  ~OpenGLWidget() = default;

protected:
  /// @brief Overrides of QOpenGLWidget
  /// @{
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  // void mouseMoveEvent(QMouseEvent* mouse_event) override;
  // void mousePressEvent(QMouseEvent* mouse_event) override;
  // void wheelEvent(QWheelEvent* wheel_event) override;
  /// @}

private:
  void load_shaders();

private:
  int32_t width_;
  int32_t height_;

  std::unique_ptr<ShaderProgram> shader_program_;
  Eigen::Matrix4d projection_matrix_;
  ViewpointCamera viewpoint_camera_;
  std::unique_ptr<GraphicsObject> graphics_object_;
};
