#pragma once

#include <QOpenGLFunctions_4_3_Core>

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

class OpenGLInterface
{
public:
  using OpenGLFunctions = QOpenGLFunctions_4_3_Core;

public:
  OpenGLInterface() = delete;

  static OpenGLFunctions* get_api();
  static void set_api(OpenGLFunctions* funcs);

private:
  static OpenGLFunctions* gl_funcs_;
};
