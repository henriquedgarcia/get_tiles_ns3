#ifndef TYPES_H
#define TYPES_H

#include <array>  // std::array
#include <cmath>
#include <opencv2/core.hpp>  // CV_PI
#include <string>            // std::string
#include <variant>           // std::variant
#include <vector>            // std::vector

#define PI     3.1415926535897932384626433832795          // PI
#define PI_2   1.5707963267948966192313216916398    // PI / 2
#define TWO_PI 6.283185307179586476925286766559  // 2 * PI

using PointYawPitchRoll = cv::Vec3d;  // (yaw, pitch, roll) (double)
using AePoint           = cv::Vec2d;  // (azimuth, elevation) (double)
using Point3D           = cv::Vec3d;  // (x, y, z) (double)
using PointUV           = cv::Vec2d;  // (u, v) (double)
using PointMN           = cv::Vec2d;  // (m, n) (unsingned short int) - 0-65535
using Resolution        = cv::Vec2d;  // (W, H) (unsingned short int) - 0-65535
using Tiling            = cv::Vec2d;  // (W, H) (unsingned char) - 0-255
using Fov               = cv::Vec2d;  // (fov_x, fov_y) (double)
using Normal            = cv::Vec3d;

using GridPoint3D = cv::Mat_<Point3D>;
using GridPointMN = cv::Mat_<PointMN>;

extern const cv::Vec3d AXIS_X;
extern const cv::Vec3d AXIS_Y;
extern const cv::Vec3d AXIS_Z;

struct Frustrum {
  std::array<Normal, 4> normals;  // left, right, top, bottom

  Frustrum(Normal normal_left   = {},
           Normal normal_right  = {},
           Normal normal_top    = {},
           Normal normal_bottom = {})
      : normals({normal_left,
                 normal_right,
                 normal_top,
                 normal_bottom}) {}

  bool operator==(const Frustrum& other) const {
    return normals == other.normals;
  }
};

struct Tile {
  int index;
  Resolution resolution;
  PointMN position;
  std::vector<PointMN> borders;
  std::vector<Point3D> borders_xyz;

  Tile(int index,
       const Resolution& resolution,
       const PointMN& position,
       const std::vector<PointMN>& borders = {})
      : index(index),
        resolution(resolution),
        position(position),
        borders(borders) {}
};

using Field = std::variant<int, double, std::string>;
using Row   = std::vector<Field>;  // A row in a CSV file

#endif  // TYPES_H
