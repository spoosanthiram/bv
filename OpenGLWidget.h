#pragma once

#include "ShaderProgram.h"

#include <QOpenGLWidget>

#include <memory>

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
  std::unique_ptr<ShaderProgram> shader_program_;

  int32_t width_{1600};
  int32_t height_{900};
};
