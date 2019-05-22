cmake_minimum_required(VERSION 3.0)

project(bv CXX)

add_compile_options(-Wall -std=c++1y)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

add_executable(BrainViewer
  # Headers
  MainWindow.h
  OpenGLInterface.h
  OpenGLWidget.h

  # Sources
  main.cpp
  MainWindow.cpp
  OpenGLInterface.cpp
  OpenGLWidget.cpp
)

target_link_libraries(BrainViewer
  Qt5::Widgets
  Qt5::Gui
  Qt5::Core
  stdc++
)
