#include "MainWindow.h"

constexpr int INITIAL_WIDTH = 1300;
constexpr int INITIAL_HEIGHT = 900;

MainWindow::MainWindow()
{
  setWindowTitle("Brain Viewer");
  setGeometry(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);

  gl_view_ = new OpenGLWidget{this};
  setCentralWidget(gl_view_);
}

void MainWindow::update()
{
  gl_view_->update_graphics_object();
}

void MainWindow::closeEvent(QCloseEvent* close_event)
{
  window_closed_ = true;
}
