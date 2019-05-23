cmake_minimum_required(VERSION 3.0)

project(bv CXX)

add_compile_options(-Wall -std=c++1y)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

include_directories(3rd_party)

add_executable(BrainViewer
  # Headers
  GeometryTypes.h
  GraphicsObject.h
  MainWindow.h
  OpenGLInterface.h
  OpenGLWidget.h
  RenderObject.h
  Shader.h
  ShaderProgram.h
  ViewpointCamera.h

  # Sources
  GraphicsObject.cpp
  main.cpp
  MainWindow.cpp
  OpenGLInterface.cpp
  OpenGLWidget.cpp
  RenderObject.cpp
  Shader.cpp
  ShaderProgram.cpp
  ViewpointCamera.cpp
)

target_link_libraries(BrainViewer
  Qt5::Widgets
  Qt5::Gui
  Qt5::Core
  stdc++
)
