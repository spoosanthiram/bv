#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
  program_id_ = OpenGLInterface::get_api()->glCreateProgram();
  if (program_id_ == 0)
    throw std::runtime_error{"Failed to create shader program."};
}

ShaderProgram::~ShaderProgram()
{
  auto gl_api = OpenGLInterface::get_api();
  for (const auto& shader : shaders_)
  {
    gl_api->glDetachShader(program_id_, shader.get_shader_id());
  }
  gl_api->glDeleteProgram(program_id_);
}
