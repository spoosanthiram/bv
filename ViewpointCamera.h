#pragma once

#include "GeometryTypes.h"

#include <Eigen/Geometry>

/// @brief ViewpointCamera abstracts eye location with rotation
class ViewpointCamera
{
public:
  ViewpointCamera();
  ~ViewpointCamera() = default;

  ViewpointCamera(const ViewpointCamera& other) = delete;
  ViewpointCamera& operator=(const ViewpointCamera& other) = delete;
  ViewpointCamera(ViewpointCamera&& other) = delete;
  ViewpointCamera& operator=(ViewpointCamera&& other) = delete;

  /// @brief Get the view matrix
  const Eigen::Matrix4d& get_view_matrix() const { return view_matrix_; }

  /// @brief Zoom by moving the eye point
  void zoom(int steps);

  /// @brief Rotate the viewpoint using screen positions modeling hemisphere
  void rotate(const Point2d& start_position, const Point2d& end_position);

private:
  /// @brief Project screen position to an unit sphere
  Vector3d project_to_sphere(const Point2d& position) const;

  /// @brief update the view matrix based on current transformation
  void update_view_matrix();

private:
  Point3d eye_position_{0.0, 0.0, 5.0};

  double zoom_level_{0.5};
  Eigen::Transform<double, 3, Eigen::Affine> eye_rotation_matrix_;

  Eigen::Matrix4d view_matrix_;
};
