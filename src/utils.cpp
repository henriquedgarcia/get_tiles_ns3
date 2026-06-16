#include "utils.hpp"
#include "projection.hpp"
#include "types.hpp"
#include <fstream> // std::ofstream, std::ifstream
#include <iostream>
#include <numeric> // std::iota
#include <opencv2/core/quaternion.hpp>
#include <sstream> // std::stringstream
#include <vector>  // std::vector

std::pair<double, double> linear_regression(const std::vector<double> &y) {
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

std::vector<Point3D> predict_future(const std::vector<Point3D> &data,
                                    int n_future) {
  int n_input = (int)data.size();

  // extrair cada coordenada
  std::vector<double> xs(n_input), ys(n_input), zs(n_input);
  for (int i = 0; i < n_input; ++i) {
    xs[i] = data[i][0];
    ys[i] = data[i][1];
    zs[i] = data[i][2];
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

std::vector<double>
linspace(const double start, const double end, const int num_points) {
  double step = (end - start) / (num_points - 1);

  std::vector<double> output;
  for (int i = 0; i < num_points; ++i) {
    output.push_back(start + i * step);
  }
  return output;
}

std::vector<Tile> make_tile_list(Projection *projection) {
  int index = 0;
  std::vector<Tile> vptiles;
  assert(projection != nullptr);
  for (int h = 0; h < projection->tiling[1]; h++) {
    for (int w = 0; w < projection->tiling[0]; w++) {
      PointMN position(w * (projection->tile_resolution[0]),
                       h * (projection->tile_resolution[1]));
      Tile tile(index, projection->tile_resolution, position);
      tile.borders = get_tile_borders(tile);

      // make tile borders
      tile.borders_xyz = std::vector<Point3D>();
      for (const auto &border : tile.borders) {
        Point3D point = projection->mn2xyz(border);
        tile.borders_xyz.push_back(point);
      }

      vptiles.push_back(tile);
      index++;
    }
  }
  return vptiles;
}

std::vector<PointMN> get_tile_borders(const Tile &tile) {
  std::vector<PointMN> borders;

  int left_x = tile.position[0];
  int right_x = tile.position[0] + tile.resolution[0];
  int top_y = tile.position[1];
  int bottom_y = tile.position[1] + tile.resolution[1];

  for (int x = left_x; x < right_x; x++) {
    borders.push_back(PointMN(x, top_y));    // Top edge
    borders.push_back(PointMN(x, bottom_y)); // Bottom edge
  }

  for (int y = top_y; y < bottom_y; y++) {
    borders.push_back(PointMN(left_x, y));  // Left edge
    borders.push_back(PointMN(right_x, y)); // Right edge
  }

  return borders;
};

Frustrum create_default_frustrum(Fov fov) {
  // somente para fov < 180°
  double fov_w_2 = fov[0] / 2;
  double fov_h_2 = fov[1] / 2;

  double sin_fov_w_2 = std::sin(fov_w_2);
  double cos_fov_w_2 = std::cos(fov_w_2);
  double sin_fov_h_2 = std::sin(fov_h_2);
  double cos_fov_h_2 = std::cos(fov_h_2);

  Normal normal_left(-sin_fov_w_2, 0.0, -cos_fov_w_2);
  Normal normal_right(-sin_fov_w_2, 0.0, cos_fov_w_2);
  Normal normal_top(-sin_fov_h_2, cos_fov_h_2, 0.0);
  Normal normal_bottom(-sin_fov_h_2, -cos_fov_h_2, 0.0);

  Frustrum frustrum(normal_left, normal_right, normal_top, normal_bottom);
  return frustrum;
}
