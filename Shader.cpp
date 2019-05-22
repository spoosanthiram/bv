#include "Shader.h"

std::string shader_type_str(GLenum shader_type)
{
  switch (shader_type)
  {
  case GL_VERTEX_SHADER:
    return "Vertex Shader";
  case GL_FRAGMENT_SHADER:
    return "Fragment Shader";
  default:
    return "Unknown Shader";
  }
}

Shader::Shader(GLenum shader_type)
  : shader_type_{shader_type}
{
  shader_id_ = OpenGLInterface::get_api()->glCreateShader(shader_type_);
  if (shader_id_ == 0)
  {
    throw std::runtime_error{"Could not create " + shader_type_str(shader_type_)};
  }
}

Shader::~Shader()
{
  if (shader_id_ != 0)
  {
    OpenGLInterface::get_api()->glDeleteShader(shader_id_);
  }
}
