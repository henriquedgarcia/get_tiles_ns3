#include "utils.h"

#include <fstream> // std::ofstream, std::ifstream
#include <iostream>
#include <numeric> // std::iota
#include <sstream> // std::stringstream
#include <vector>  // std::vector

#include "types.h"

std::pair<double, double> linear_regression(const std::vector<double>& y) {
    int n = (int)y.size();
    std::vector<double> x(n);
    std::iota(x.begin(), x.end(), 0);

    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_x2 = 0.0, sum_xy = 0.0;

    for (int i = 0; i < n; ++i) {
        sum_x2 += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    double denom = n * sum_x2 - sum_x * sum_x;
    double a = (n * sum_xy - sum_x * sum_y) / denom;
    double b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;

    return {a, b};
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
                                    int n_future) {
    int n_input = (int) data.size();

    // extrair cada coordenada
    std::vector<double> xs(n_input), ys(n_input), zs(n_input);
    for (int i = 0; i < n_input; ++i) {
        xs[i] = data[i].x;
        ys[i] = data[i].y;
        zs[i] = data[i].z;
    }

    // regressão linear separada
    auto [ax, bx] = linear_regression(xs);
    auto [ay, by] = linear_regression(ys);
    auto [az, bz] = linear_regression(zs);

    // prever próximos 30 pontos
    std::vector<Point3D> future;
    int start = n_input, end = n_input + n_future;

    for (int i = start; i < end; ++i) {
        double fx = ax * i + bx;
        double fy = ay * i + by;
        double fz = az * i + bz;
        future.push_back({fx, fy, fz});
    }

    return future;
}
