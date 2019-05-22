#include "ShaderProgram.h"

#include <iostream>

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
    gl_api->glDetachShader(program_id_, shader.get_shader_id());

  gl_api->glDeleteProgram(program_id_);
}

void ShaderProgram::attach_shader(Shader&& shader)
{
  auto gl_api = OpenGLInterface::get_api();

  gl_api->glAttachShader(program_id_, shader.get_shader_id());
  if (gl_api->glGetError() != GL_NO_ERROR)
    throw std::runtime_error{"Failed to attach " + shader.get_type_str() + " shader."};

  shaders_.emplace_back(std::move(shader));
}

void ShaderProgram::link() const
{
  if (shaders_.empty()) {
    std::cerr << "No shaders attached for linking.";
    return;
  }

  auto gl_api = OpenGLInterface::get_api();

  gl_api->glLinkProgram(program_id_);

  GLint is_linked;
  gl_api->glGetProgramiv(program_id_, GL_LINK_STATUS, &is_linked);
  if (!is_linked) {
    constexpr int32_t LOG_LENGTH = 1024;
    GLsizei log_lenth;
    char log[LOG_LENGTH];
    gl_api->glGetProgramInfoLog(program_id_, LOG_LENGTH, &log_lenth, static_cast<char*>(log));
    throw std::runtime_error{std::string{"Failed to link the shader program. Error: "} + log};
  }
}