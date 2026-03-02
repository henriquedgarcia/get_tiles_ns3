#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <numbers> // pi
#include <numeric> // std::iota
#include <vector>

#include "types.h" // Point3D

inline double deg2rad(double deg) { return deg * std::numbers::pi / 180.0; }

inline double rad2deg(double rad) { return rad * 180.0 / std::numbers::pi; }

inline Point3D normalize(Point3D p) {
    double norm = std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    return {p.x / norm, p.y / norm, p.z / norm};
}

inline double dot(const Point3D& a, const Point3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
                                    int n_future = 30);
std::pair<double, double> linear_regression(const std::vector<double>& y);

#endif // UTILS_H
