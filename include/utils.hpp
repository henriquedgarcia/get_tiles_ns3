#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <numbers>  // pi
#include <numeric>  // std::iota
#include <opencv2/opencv.hpp>
#include <vector>
#include "types.hpp"  // Point3D

inline double deg2rad(double deg) { return deg * std::numbers::pi / 180.0; }

inline double rad2deg(double rad) { return rad * 180.0 / std::numbers::pi; }

inline Point3D normalize(Point3D p) { return cv::normalize(p); }

inline double dot(const Point3D& a,
                  const Point3D& b) {
  return a.dot(b);
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
                                    int n_future = 30);

std::pair<double,
          double>

linear_regression(const std::vector<double>& y);

std::vector<double> linspace(const double start,
                             const double end,
                             const int num_points);

cv::Mat applyRotation(const cv::Mat& points,
                      const cv::Mat& R);

void make_tile_list();

std::vector<PointMN> get_tile_borders(const Tile& tile);

#endif  // UTILS_H
