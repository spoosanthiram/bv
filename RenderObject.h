#pragma once

#include "GeometryTypes.h"
#include "OpenGLInterface.h"

#include <memory>

class ShaderProgram;

/// @brief Class abstract the information to be used for rendering.
///        Usually initialized once and used in drawing loop
class RenderObject {
public:
  RenderObject() = default;
  ~RenderObject();

  RenderObject(const RenderObject &other) = delete;
  RenderObject &operator=(const RenderObject &other) = delete;
  RenderObject(RenderObject &&other) noexcept;
  RenderObject &operator=(RenderObject &&other) noexcept;

  /// @brief Initialize with graphics geometry
  void init(const GraphicsGeometry &graphics_geometry);

  /// @brief Render the object using the shader program
  void render(const std::unique_ptr<ShaderProgram> &shader_program) const;

private:
  /// @brief Vertex array & buffer object ids
  GLuint vao_{0};
  GLuint position_bo_{0};
  GLuint normal_bo_{0};
  GLuint color_bo_{0};
  GLuint index_bo_{0};

  /// @brief Number of indices needed to render
  uint32_t indices_size_{0};
};
