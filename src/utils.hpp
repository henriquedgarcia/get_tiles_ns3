#ifndef UTILS_H
#define UTILS_H

#include "projection.hpp"
#include "types.hpp" // Point3D
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

inline double deg2rad(double deg) { return deg * PI / 180.0; }

inline double rad2deg(double rad) { return rad * 180.0 / PI; }

inline double dot(const Point3D &a, const Point3D &b) { return a.dot(b); }

std::vector<Point3D>
predict_future(const std::vector<Point3D> &data, int n_future = 30);

std::pair<double, double>

linear_regression(const std::vector<double> &y);

std::vector<double>
linspace(const double start, const double end, const int num_points);

std::vector<Tile> make_tile_list(Projection *projection);

std::vector<PointMN> get_tile_borders(const Tile &tile);

#endif // UTILS_H
