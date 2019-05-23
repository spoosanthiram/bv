#pragma once

#include <Eigen/Core>

#include <vector>

using Point3f = Eigen::Vector3f;
using Point4f = Eigen::Vector4f;
using Vector3f = Eigen::Vector3f;

/// @brief Struct to keep the relevant geometry info that can be
///        directly used in a graphics pipeline
struct GraphicsGeometry
{
  size_t vertex_positions_buffer_size() const { return vertex_positions.size() * sizeof(Point3f); }
  size_t vertex_normals_buffer_size() const { return vertex_normals.size() * sizeof(Vector3f); }
  size_t vertex_colors_buffer_size() const { return vertex_colors.size() * sizeof(Point4f); }
  size_t indices_buffer_size() const { return indices.size() * sizeof(uint32_t); }

  std::vector<Point3f> vertex_positions;
  std::vector<Vector3f> vertex_normals;
  std::vector<Point4f> vertex_colors;
  std::vector<uint32_t> indices;
};
