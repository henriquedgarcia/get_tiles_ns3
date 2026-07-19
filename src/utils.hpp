#ifndef UTILS_H
#define UTILS_H

#include "projection.hpp"
#include "types.hpp" // Point3D
#include <cmath>
#include <opencv2/core/quaternion.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

static const auto angle_type = cv::QuatEnum::EulerAnglesType::INT_YXZ;

inline cv::Quatd create_quaternion(const PointYawPitchRoll &yaw_pitch_roll) {
  return cv::Quatd::createFromEulerAngles(yaw_pitch_roll, angle_type);
}

inline double to_int(double x) { return static_cast<int>(x); }

inline double to_double(int x) { return static_cast<double>(x); }

inline double deg2rad(double deg) { return deg * PI / 180.0; }

inline double rad2deg(double rad) { return rad * 180.0 / PI; }

inline double dot(const Point3D &a, const Point3D &b) { return a.dot(b); }

void rotate_grid(const GridPoint3D &xyz_grid_default,
                 const PointYawPitchRoll &yaw_pitch_roll,
                 GridPoint3D &xyz_grid_rotated);

Point3D rotate(const Point3D &point, const cv::Quatd &quat);

std::vector<Point3D> predict_future(const std::vector<Point3D> &data,
                                    int n_future = 30);

std::pair<double, double> linear_regression(const std::vector<double> &y);

std::vector<double> linspace(double start, double end, int n_points);

std::vector<Tile> make_tile_list(Projection *projection);

std::vector<PointMN> get_tile_borders(const Tile &tile);

Frustrum create_default_frustrum(Fov fov);

#endif // UTILS_H
