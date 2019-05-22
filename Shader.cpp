#include "Shader.h"

#include <fstream>

Shader::Shader(GLenum shader_type)
  : shader_type_{shader_type}
{
  shader_id_ = OpenGLInterface::get_api()->glCreateShader(shader_type_);
  if (shader_id_ == 0)
    throw std::runtime_error{"Could not create " + get_type_str()};
}

Shader::~Shader()
{
  if (shader_id_ != 0)
    OpenGLInterface::get_api()->glDeleteShader(shader_id_);
}

std::string Shader::get_type_str() const
{
  switch (shader_type_)
  {
  case GL_VERTEX_SHADER:
    return "Vertex Shader";
  case GL_FRAGMENT_SHADER:
    return "Fragment Shader";
  default:
    return "Unknown Shader";
  }
}

void Shader::compile(const std::string& file_path)
{
  auto gl_api = OpenGLInterface::get_api();

  std::ifstream input_stream{file_path};
  std::string file_content{std::istreambuf_iterator<char>{input_stream}, std::istreambuf_iterator<char>{}};

  auto source = file_content.c_str();
  gl_api->glShaderSource(shader_id_, 1, &source, nullptr);

  gl_api->glCompileShader(shader_id_);

  GLint is_compiled;
  gl_api->glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &is_compiled);
  if (!is_compiled) {
    constexpr int32_t LOG_LENGTH = 1024;
    GLsizei log_lenth;
    char log[LOG_LENGTH];
    gl_api->glGetShaderInfoLog(shader_id_, LOG_LENGTH, &log_lenth, static_cast<char*>(log));
    throw std::runtime_error{get_type_str() + " compilation failed. Error: " + log};
  }
}
