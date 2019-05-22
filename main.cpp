#include "MainWindow.h"

#include <QApplication>

#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
  try {
    QApplication app{argc, argv};

    MainWindow main_window;
    main_window.show();

    app.exec();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
