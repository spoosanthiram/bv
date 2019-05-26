#include "MainWindow.h"

#include <QApplication>

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
  try {
    QApplication app{argc, argv};

    MainWindow main_window;
    main_window.show();

    while (true) {
      main_window.update();
      app.processEvents();

      if (main_window.is_closed())
        break;

      std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
