#pragma once

#include "OpenGLInterface.h"

/// @brief Class for OpenGL shader currenty supporting VERTEX and FRAGMENT
/// shader
class Shader
{
public:
  explicit Shader(GLenum shader_type);
  ~Shader();

  Shader(const Shader& other) = delete;
  Shader& operator=(const Shader& other) = delete;

  Shader(Shader&& other) noexcept : shader_type_{other.shader_type_}, shader_id_{other.shader_id_}
  {
    other.shader_type_ = 0;
    other.shader_id_ = 0;
  }

  Shader& operator=(Shader&& other) noexcept
  {
    shader_type_ = other.shader_type_;
    shader_id_ = other.shader_id_;

    other.shader_type_ = 0;
    other.shader_id_ = 0;

    return *this;
  }

  /// @brief Get OpenGL shader id
  GLuint get_shader_id() const { return shader_id_; }

  /// @brief Get type of the shader as string
  std::string get_type_str() const;

  /// @brief Compile the shader code from a file
  void compile(const std::string& file_path);

private:
  GLenum shader_type_;
  GLuint shader_id_{0};
};
