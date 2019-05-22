#include "MainWindow.h"

#include <QApplication>

#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app{argc, argv};

  try {
    MainWindow main_window;
    main_window.show();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  app.exec();

  return 0;
}
