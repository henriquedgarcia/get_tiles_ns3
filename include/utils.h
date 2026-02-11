#ifndef UTILS_H
#define UTILS_H

#include <numbers> // pi
#include <vector>
#include <numeric> // std::iota
#include <cmath>

#include "types.h" // Point3D

inline double deg2rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}

inline double rad2deg(double rad) {
    return rad * 180.0 / std::numbers::pi;
}

std::vector<Point3D> predict_future(const std::vector<Point3D> &data, int n_future = 30);
std::pair<double,double> linear_regression(const std::vector<double>& y);







#endif // UTILS_H
