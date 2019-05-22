#pragma once

#include "OpenGLWidget.h"

#include <QMainWindow>
#include <QPointer>

class MainWindow : public QMainWindow
{
public:
  MainWindow();
  ~MainWindow() = default;

private:
  QPointer<OpenGLWidget> gl_view_;
};
