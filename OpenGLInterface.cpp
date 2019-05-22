#include "OpenGLInterface.h"

OpenGLInterface::OpenGLFunctions* OpenGLInterface::gl_funcs_ = nullptr;

OpenGLInterface::OpenGLFunctions* OpenGLInterface::get_api()
{
  return gl_funcs_;
}

void OpenGLInterface::set_api(OpenGLFunctions* funcs)
{
  gl_funcs_ = funcs;
}
