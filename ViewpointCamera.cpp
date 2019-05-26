#include "ViewpointCamera.h"

ViewpointCamera::ViewpointCamera()
{
  eye_rotation_matrix_.setIdentity();
  update_view_matrix();
}

void ViewpointCamera::zoom(int steps)
{
  constexpr double ZOOM_SCALE = 0.05;
  zoom_level_ -= steps * ZOOM_SCALE;
  update_view_matrix();
}

void ViewpointCamera::rotate(const Point2d& start_position, const Point2d& end_position)
{
  // project the normalized screen point to unit sphere
  Vector3d start_pos_on_sphere = project_to_sphere(start_position);
  Vector3d end_pos_on_sphere = project_to_sphere(end_position);

  // find angle and rotation axis
  double angle =
    std::acos(start_pos_on_sphere.dot(end_pos_on_sphere) / (start_pos_on_sphere.norm() * end_pos_on_sphere.norm()));
  Vector3d axis = end_pos_on_sphere.cross(start_pos_on_sphere);
  axis.normalize();

  eye_rotation_matrix_.rotate(Eigen::AngleAxis<double>{angle, axis});

  update_view_matrix();
}

Vector3d ViewpointCamera::project_to_sphere(const Point2d& position) const
{
  Vector3d pos_on_sphere{position.x(), position.y(), 0.0};
  double norm = pos_on_sphere.norm();
  if (norm > 1.0) {
    pos_on_sphere.normalize();
  }
  else {
    pos_on_sphere[2] = std::sqrt(1.0 - norm * norm);
  }

  Vector3d eye = eye_position_;
  Vector3d up = Vector3d{0.0, 1.0, 0.0};
  Vector3d side = up.cross(eye);

  side = side.normalized() * pos_on_sphere.x();
  up = up.normalized() * pos_on_sphere.y();
  eye = eye.normalized() * pos_on_sphere.z();

  return eye + up + side;
}

void ViewpointCamera::update_view_matrix()
{
  auto rotation_matrix = eye_rotation_matrix_.linear();

  Vector3d eye = rotation_matrix * eye_position_;
  eye *= zoom_level_;

  Vector3d w = eye;
  w.normalize();

  Vector3d up_vector = rotation_matrix * Vector3d{0.0, 1.0, 0.0};

  Vector3d u = up_vector.cross(w);
  u.normalize();

  Vector3d v = w.cross(u);

  Vector3d negative_eye{-eye.x(), -eye.y(), -eye.z()};

  view_matrix_(0, 0) = u.x();
  view_matrix_(0, 1) = u.y();
  view_matrix_(0, 2) = u.z();
  view_matrix_(0, 3) = negative_eye.dot(u);

  view_matrix_(1, 0) = v.x();
  view_matrix_(1, 1) = v.y();
  view_matrix_(1, 2) = v.z();
  view_matrix_(1, 3) = negative_eye.dot(v);

  view_matrix_(2, 0) = w.x();
  view_matrix_(2, 1) = w.y();
  view_matrix_(2, 2) = w.z();
  view_matrix_(2, 3) = negative_eye.dot(w);

  view_matrix_(3, 0) = 0.0;
  view_matrix_(3, 1) = 0.0;
  view_matrix_(3, 2) = 0.0;
  view_matrix_(3, 3) = 1.0;
}
