#include "ViewpointCamera.h"

ViewpointCamera::ViewpointCamera()
{
  eye_rotation_matrix_.setIdentity();
  update_view_matrix();
}

void ViewpointCamera::update_view_matrix()
{
  auto rotation_matrix = eye_rotation_matrix_.linear();

  Eigen::Vector3d eye = rotation_matrix * eye_position_;
  eye *= zoom_level_;

  Eigen::Vector3d w = eye;
  w.normalize();

  Eigen::Vector3d up_vector = rotation_matrix * Eigen::Vector3d{0.0, 1.0, 0.0};

  Eigen::Vector3d u = up_vector.cross(w);
  u.normalize();

  Eigen::Vector3d v = w.cross(u);

  Eigen::Vector3d negative_eye{-eye.x(), -eye.y(), -eye.z()};

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
