#pragma once

#include "OpenGLInterface.h"
#include "Shader.h"

#include <Eigen/Core>

#include <unordered_map>
#include <vector>

/// @brief Class for OpenGL shader program
class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

  ShaderProgram(const ShaderProgram& other) = delete;
  ShaderProgram& operator=(const ShaderProgram& other) = delete;
  ShaderProgram(ShaderProgram&& other) = delete;
  ShaderProgram& operator=(ShaderProgram&& other) = delete;

  /// @brief Get shader program id
  GLuint get_program_id() const { return program_id_; }

  /// @brief Attach vertex or fragement shader
  void attach_shader(Shader&& shader);

  /// @brief link the compiled shaders.
  void link() const;

  /// @brief Set the GLSL uniform matrix 4x4 value
  void set_matrix(const std::string& name, const Eigen::Matrix4d& matrix);

private:
  /// @brief Look up GLSL uniform location id in the stored map.
  ///        Get uniform location id and add to map if look up fails
  GLint lookup_location(const std::string& name);

private:
  GLuint program_id_{0};
  std::vector<Shader> shaders_;
  std::unordered_map<std::string, GLint> location_map_;
};
