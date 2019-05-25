#include "GraphicsObject.h"

#include <fstream>
#include <unordered_map>

GraphicsObject::GraphicsObject(const std::string& file_path)
{
  const auto graphics_geometry = read_model(file_path);
  render_object_.init(graphics_geometry);

  // create 2nd render object
  std::unordered_map<uint32_t, uint32_t> index_map;
  GraphicsGeometry graphics_geometry2;
  for (uint32_t i = 0; i < 1800; ++i)
  {
    auto index = graphics_geometry.indices[i];
    if (index_map.find(index) == index_map.end())
    {
      index_map[index] = graphics_geometry2.vertex_positions.size();

      graphics_geometry2.vertex_positions.push_back(graphics_geometry.vertex_positions[index]);
      graphics_geometry2.vertex_normals.push_back(graphics_geometry.vertex_normals[index]);
      graphics_geometry2.vertex_colors.push_back(Point4f{1.0f, 1.0f, 1.0f, 1.0f});
    }
    graphics_geometry2.indices.push_back(index_map[index]);
  }

  render_object2_.init(graphics_geometry2);
}

void GraphicsObject::render(const std::unique_ptr<ShaderProgram>& shader_program) const
{
  render_object_.render(shader_program);
  render_object2_.render(shader_program);
}

GraphicsGeometry GraphicsObject::read_model(const std::string& file_path) const
{
  std::ifstream bin_stream{file_path, std::ios::binary};
  if (!bin_stream)
    throw std::runtime_error{"Could not open " + file_path};

  // number of vertices
  uint32_t num_vertices = 0;
  bin_stream.read(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));

  GraphicsGeometry graphics_geometry;

  // vertices
  {
    graphics_geometry.vertex_positions.reserve(num_vertices);
    graphics_geometry.vertex_normals.reserve(num_vertices);
    graphics_geometry.vertex_colors.reserve(num_vertices);

    Point3f pos;
    Vector3f normal;
    Point4f color;
    for (uint32_t i = 0; i < num_vertices; ++i) {
      bin_stream.read(reinterpret_cast<char*>(pos.data()), sizeof(pos));
      bin_stream.read(reinterpret_cast<char*>(normal.data()), sizeof(normal));
      bin_stream.read(reinterpret_cast<char*>(color.data()), sizeof(color));

      graphics_geometry.vertex_positions.push_back(pos);
      graphics_geometry.vertex_normals.push_back(normal);
      graphics_geometry.vertex_colors.push_back(color);
    }
  }

  // number of triangles
  uint32_t num_triangles = 0;
  bin_stream.read(reinterpret_cast<char*>(&num_triangles), sizeof(num_triangles));

  // indices
  {
    graphics_geometry.indices.reserve(num_triangles * 3);

    uint32_t val = 0;
    for (uint32_t i = 0; i < num_triangles; ++i) {
      for (int j = 0; j < 3; ++j) {
        bin_stream.read(reinterpret_cast<char*>(&val), sizeof(val));
        graphics_geometry.indices.push_back(val);
      }
    }
  }

  return graphics_geometry;
}
