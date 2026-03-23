#include "utils.hpp"
#include <fstream>  // std::ofstream, std::ifstream
#include <iostream>
#include <numeric>  // std::iota
#include <opencv2/core/quaternion.hpp>
#include <sstream>  // std::stringstream
#include <vector>   // std::vector
#include "types.hpp"

std::pair<double,
          double>

linear_regression(const std::vector<double>& y) {
  int n = (int)y.size();
  std::vector<double> x(n);
  std::iota(x.begin(), x.end(), 0);

  double sum_x  = std::accumulate(x.begin(), x.end(), 0.0);
  double sum_y  = std::accumulate(y.begin(), y.end(), 0.0);
  double sum_x2 = 0.0, sum_xy = 0.0;

  for (int i = 0; i < n; ++i) {
    sum_x2 += x[i] * x[i];
    sum_xy += x[i] * y[i];
  }

  double denom = n * sum_x2 - sum_x * sum_x;
  double a     = (n * sum_xy - sum_x * sum_y) / denom;
  double b     = (sum_y * sum_x2 - sum_x * sum_xy) / denom;

  return {a, b};
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
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

std::vector<double> linspace(const double start,
                             const double end,
                             const int num_points) {
  double step = (end - start) / (num_points - 1);

  std::vector<double> output;
  for (int i = 0; i < num_points; ++i) {
    output.push_back(start + i * step);
  }
  return output;
}

cv::Mat applyRotation(const GridPoint3D xyz_grid_default,
                      const cv::Quatd quat) {
  int rows = xyz_grid_default.rows;
  int cols = xyz_grid_default.cols;

  GridPoint3D xyz_grid_rotated = xyz_grid_default.clone();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cv::Quatd q_vector       = cv::Quatd(0,
                                     xyz_grid_default(i, j)[0],
                                     xyz_grid_default(i, j)[1],
                                     xyz_grid_default(i, j)[2]);
      cv::Quatd quat_conjugate = quat.conjugate();
      cv::Quatd result         = quat * q_vector * quat_conjugate;
      xyz_grid_rotated(i, j)   = cv::Vec3d(result.x, result.y, result.z);
    }
  }

  return xyz_grid_rotated;
}


vector<Tile> make_tile_list(Projection* projection) {
  int index = 0;
  vector<Tile> vptiles;

  for (int h = 0; h < projection->tiling[1]; h++) {
    for (int w = 0; w < projection->tiling[0]; w++) {
      PointMN position(w * (projection->tile_resolution[0]),
                       h * (projection->tile_resolution[1]));
      Tile tile(index, projection->tile_resolution, position);
      tile.borders = get_tile_borders(tile);

      vector<Point3D> xyz_points;
      for (const auto& border : tile.borders) {
        xyz_points.push_back(projection->mn2xyz(border));
      }
      tile.borders_xyz = xyz_points;

      vptiles.push_back(tile);
      index++;
    }
  }
  return vptiles;
}

vector<PointMN> get_tile_borders(const Tile& tile) {
  vector<PointMN> borders;

  int left_x   = tile.position[0];
  int right_x  = tile.position[0] + tile.resolution[0];
  int top_y    = tile.position[1];
  int bottom_y = tile.position[1] + tile.resolution[1];

  for (int x = left_x; x < right_x; x++) {
    borders.push_back(PointMN(x, top_y));     // Top edge
    borders.push_back(PointMN(x, bottom_y));  // Bottom edge
  }
  for (int y = top_y; y < bottom_y; y++) {
    borders.push_back(PointMN(left_x, y));   // Left edge
    borders.push_back(PointMN(right_x, y));  // Right edge
  }

  return borders;
};

