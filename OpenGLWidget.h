#pragma once

#include <QOpenGLWidget>

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
  int32_t width_{1600};
  int32_t height_{900};
};
