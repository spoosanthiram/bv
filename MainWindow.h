#pragma once

#include "OpenGLWidget.h"

#include <QMainWindow>
#include <QPointer>

class MainWindow : public QMainWindow
{
public:
  MainWindow();
  ~MainWindow() = default;

  bool is_closed() const { return window_closed_; }
  void update();

protected:
  void closeEvent(QCloseEvent* close_event) override;

private:
  QPointer<OpenGLWidget> gl_view_;
  bool window_closed_{false};
};
