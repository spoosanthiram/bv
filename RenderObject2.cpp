#include "RenderObject2.h"

#include "ShaderProgram.h"

#include <iostream>

constexpr uint32_t SHADER_VERTEX_POSITION = 0;
constexpr uint32_t SHADER_VERTEX_NORMAL = 1;

RenderObject2::~RenderObject2()
{
  // vertex array object id == 0 implies the buffers are not created, no clean up needed
  if (vao_ == 0)
    return;

  auto gl_funcs = OpenGLInterface::get_api();

  gl_funcs->glDeleteBuffers(1, &position_bo_);
  gl_funcs->glDeleteBuffers(1, &normal_bo_);
  gl_funcs->glDeleteBuffers(1, &index_bo_);

  gl_funcs->glDeleteVertexArrays(1, &vao_);
}

RenderObject2::RenderObject2(RenderObject2&& other) noexcept
  : vao_{other.vao_}
  , position_bo_{other.position_bo_}
  , normal_bo_{other.normal_bo_}
  , index_bo_{other.index_bo_}
  , indices_size_{other.indices_size_}
{
  // Reset the moved object ids to 0 so the GPU buffer doesn't get deleted twice
  other.vao_ = 0;
  other.position_bo_ = 0;
  other.normal_bo_ = 0;
  other.index_bo_ = 0;
  other.indices_size_ = 0;
}

RenderObject2& RenderObject2::operator=(RenderObject2&& other) noexcept
{
  vao_ = other.vao_;
  position_bo_ = other.position_bo_;
  normal_bo_ = other.normal_bo_;
  index_bo_ = other.index_bo_;
  indices_size_ = other.indices_size_;

  // Reset the moved object ids to 0 so the GPU buffer doesn't get deleted twice
  other.vao_ = 0;
  other.position_bo_ = 0;
  other.normal_bo_ = 0;
  other.index_bo_ = 0;
  other.indices_size_ = 0;

  return *this;
}

void RenderObject2::init(const GraphicsGeometry& graphics_geometry)
{
  if (graphics_geometry.vertex_positions.empty())
    return;

  auto gl_funcs = OpenGLInterface::get_api();

  // Create OpenGL vertex array id and buffer ids
  gl_funcs->glGenVertexArrays(1, &vao_);
  gl_funcs->glGenBuffers(1, &position_bo_);
  gl_funcs->glGenBuffers(1, &normal_bo_);
  gl_funcs->glGenBuffers(1, &index_bo_);

  // Fill OpenGL buffers and set attributes
  gl_funcs->glBindVertexArray(vao_);

  // vertex position
  gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, position_bo_);
  gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                         graphics_geometry.vertex_positions_buffer_size(),
                         graphics_geometry.vertex_positions.data(),
                         GL_STATIC_DRAW);

  gl_funcs->glVertexAttribPointer(SHADER_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  gl_funcs->glEnableVertexAttribArray(SHADER_VERTEX_POSITION);

  // vertex normal
  gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, normal_bo_);
  gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                         graphics_geometry.vertex_normals_buffer_size(),
                         graphics_geometry.vertex_normals.data(),
                         GL_STATIC_DRAW);

  gl_funcs->glVertexAttribPointer(SHADER_VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  gl_funcs->glEnableVertexAttribArray(SHADER_VERTEX_NORMAL);

  // indices
  gl_funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bo_);
  gl_funcs->glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, graphics_geometry.indices_buffer_size(), graphics_geometry.indices.data(), GL_STATIC_DRAW);

  indices_size_ = graphics_geometry.indices.size();
}

void RenderObject2::render(const std::unique_ptr<ShaderProgram>& shader_program) const
{
  if (vao_ == 0)
    return;

  auto gl_funcs = OpenGLInterface::get_api();

  shader_program->set_color("color", color_);
  std::cout << "color: [" << color_[0] << ", " << color_[1] << ", " << color_[2] << ", " << color_[3] << "]\n";

  gl_funcs->glBindVertexArray(vao_);
  gl_funcs->glDrawElements(GL_TRIANGLES, indices_size_, GL_UNSIGNED_INT, nullptr);
}
