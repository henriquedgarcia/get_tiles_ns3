#ifndef UTILS_H
#define UTILS_H

#include "projection.hpp"
#include "types.hpp" // Point3D
#include <cmath>
#include <opencv2/core/quaternion.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

inline Point3D rotate(const Point3D &point, const cv::Quatd &quat) {
  cv::Quatd quat_conjugate = quat.conjugate();
  cv::Quatd q_vector = cv::Quatd(0, point[0], point[1], point[2]);
  cv::Quatd result = quat * q_vector * quat_conjugate;
  return cv::Vec3d(result.x, result.y, result.z);
}

inline cv::Quatd create_quaternion(const PointYawPitchRoll &yaw_pitch_roll) {
  auto angle_type = cv::QuatEnum::EulerAnglesType::INT_YZX;
  return cv::Quatd::createFromEulerAngles(yaw_pitch_roll, angle_type);
}

inline GridPoint3D rotate_grid(const GridPoint3D xyz_grid_default,
                               const PointYawPitchRoll &yaw_pitch_roll) {
  int rows = xyz_grid_default.rows;
  int cols = xyz_grid_default.cols;
  cv::Quatd quat = create_quaternion(yaw_pitch_roll);

  GridPoint3D xyz_grid_rotated = xyz_grid_default.clone();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      xyz_grid_rotated(i, j) = rotate(xyz_grid_default(i, j), quat);
    }
  }
  return xyz_grid_rotated;
}

inline double deg2rad(double deg) { return deg * PI / 180.0; }

inline double rad2deg(double rad) { return rad * 180.0 / PI; }

inline double dot(const Point3D &a, const Point3D &b) { return a.dot(b); }

std::vector<Point3D> predict_future(const std::vector<Point3D> &data,
                                    int n_future = 30);

std::pair<double, double> linear_regression(const std::vector<double> &y);

std::vector<double> linspace(double start, double end, int n_points);

std::vector<Tile> make_tile_list(Projection *projection);

std::vector<PointMN> get_tile_borders(const Tile &tile);

Frustrum create_default_frustrum(Fov fov);

#endif // UTILS_H
