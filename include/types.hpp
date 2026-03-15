#ifndef TYPES_H
#define TYPES_H

#include <array>  // std::array
#include <cmath>
#include <opencv2/core.hpp>  // CV_PI
#include <string>   // std::string
#include <variant>  // std::variant
#include <vector>   // std::vector

#define PI CV_PI          // PI
#define PI_2 CV_PI / 2    // PI / 2
#define TWO_PI 2 * CV_PI  // 2 * PI

using YawPitchRoll = cv::Vec3d;
using PointUV = cv::Vec2d;

struct Point3D {
  double x, y, z;

  Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  bool operator==(const Point3D& other) const { return x == other.x && y == other.y && z == other.z; }
};

struct ImagePoint {
  int m;
  int n;

  ImagePoint(int m = 0, int n = 0) : m(m), n(n) {}

  bool operator==(const ImagePoint& other) const { return m == other.m && n == other.n; }
};

struct AePoint {
  double azimuth;
  double elevation;

  AePoint(double azimuth = 0.0f, double elevation = 0.0f) : azimuth(azimuth), elevation(elevation) {}

  bool operator==(const AePoint& other) const {
    return this->azimuth == other.azimuth && this->elevation == other.elevation;
  }
};

struct Resolution {
  int w;
  int h;

  Resolution(int w = 0, int h = 0) : w(w), h(h) {}

  bool operator==(const Resolution& other) const { return w == other.w && h == other.h; }

  bool operator!=(const Resolution& other) const { return !(*this == other); }
};

using Tiling = Resolution;

struct Fov {
  // Fov em radianos
  double fov_x;
  double fov_y;

  Fov(double fov_x = 0.0, double fov_y = 0.0) : fov_x(fov_x), fov_y(fov_y) {}

  bool operator==(const Fov& other) const { return fov_x == other.fov_x && fov_y == other.fov_y; }
};

using Normal = Point3D;

struct Frustrum {
  std::array<Normal, 4> normals;  // left, right, top, bottom

  Frustrum(Normal normal_left = {}, Normal normal_right = {}, Normal normal_top = {}, Normal normal_bottom = {})
      : normals({normal_left, normal_right, normal_top, normal_bottom}) {}

  bool operator==(const Frustrum& other) const { return normals == other.normals; }
};

struct Tile {
  int index;
  Resolution resolution;
  ImagePoint position;
  std::vector<ImagePoint> borders;

  Tile(int index, const Resolution& resolution, const ImagePoint& position, const std::vector<ImagePoint>& borders = {})
      : index(index), resolution(resolution), position(position), borders(borders) {}
};

using Mat3 = std::array<std::array<double, 3>, 3>;
using Field = std::variant<int, double, std::string>;
enum class Exception { FILE_NOT_FOUND };
using Row = std::vector<Field>;  // A row in a CSV file

// alias para imagem
struct Color {
  double r, g, b;

  Color(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}

  bool operator==(const Color& other) const { return r == other.r && g == other.g && b == other.b; }
};

struct Pixel {
  Color color;
  ImagePoint im_position;
  Point3D xyz_position;

  Pixel(Color color, ImagePoint position) : color(color), im_position(position) {}

  bool operator==(const Pixel& other) const { return color == other.color && im_position == other.im_position; }
};

using VecDouble = std::vector<double>;
using Vec3D = std::vector<Point3D>;  // (x, y, z)
using ImgGrid = std::vector<std::vector<Pixel>>;

#endif  // TYPES_H
