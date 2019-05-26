#pragma once

#include "GeometryTypes.h"
#include "OpenGLInterface.h"

#include <memory>

class ShaderProgram;

/// @brief Class abstract the information to be used for rendering.
///        Usually initialized once and used in drawing loop
class RenderObject2 {
public:
  RenderObject2() = default;
  ~RenderObject2();

  RenderObject2(const RenderObject2 &other) = delete;
  RenderObject2 &operator=(const RenderObject2 &other) = delete;
  RenderObject2(RenderObject2 &&other) noexcept;
  RenderObject2 &operator=(RenderObject2 &&other) noexcept;

  /// @brief Initialize with graphics geometry
  void init(const GraphicsGeometry &graphics_geometry);

  void set_color(const Point4f &color) { color_ = color; }

  /// @brief Render the object using the shader program
  void render(const std::unique_ptr<ShaderProgram> &shader_program) const;

private:
  /// @brief Vertex array & buffer object ids
  GLuint vao_{0};
  GLuint position_bo_{0};
  GLuint normal_bo_{0};
  GLuint index_bo_{0};

  /// @brief Number of indices needed to render
  uint32_t indices_size_{0};

  Point4f color_{0.0f, 0.0f, 0.0f, 1.0f};
};
