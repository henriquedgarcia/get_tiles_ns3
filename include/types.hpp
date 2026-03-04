#ifndef TYPES_H
#define TYPES_H

#include <array> // std::array
#include <cmath>
#include <variant> // std::variant
#include <vector> // std::vector
#include <string> // std::string
#include "types.h"

#define PI 3.1415926535897932384626433832795    // PI
#define PI_2 1.5707963267948966192313216916398  // PI / 2
#define TWO_PI 6.283185307179586476925286766559 // 2 * PI

struct ViewportCoord {
    double yaw, pitch, roll;

    ViewportCoord(double yaw = 0., double pitch = 0., double roll = 0.)
        : yaw(yaw), pitch(pitch), roll(roll) {}

    bool operator==(const ViewportCoord& other) const {
        return yaw == other.yaw && pitch == other.pitch && roll == other.roll;
    }
};

struct Point3D {
    double x, y, z;

    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

using Normal = Point3D;

struct ImagePoint {
    int m;
    int n;

    ImagePoint(int m = 0, int n = 0) : m(m), n(n) {}

    bool operator==(const ImagePoint& other) const {
        return m == other.m && n == other.n;
    }
};

struct UvPoint {
    double u;
    double v;

    UvPoint(double u = 0, double v = 0) : u(u), v(v) {}

    bool operator==(const UvPoint& other) const {
        return u == other.u && v == other.v;
    }
};

struct AePoint {
    double azimuth;
    double elevation;

    AePoint(double azimuth = 0.0f, double elevation = 0.0f)
        : azimuth(azimuth), elevation(elevation) {}

    bool operator==(const AePoint& other) const {
        return this->azimuth == other.azimuth &&
               this->elevation == other.elevation;
    }
};

struct Resolution {
    int w;
    int h;

    Resolution(int w = 0, int h = 0) : w(w), h(h) {}

    bool operator==(const Resolution& other) const {
        return w == other.w && h == other.h;
    }
};

using Tiling = Resolution;

struct Fov {
    double fov_x;
    double fov_y;

    Fov(double fov_x = 0.0, double fov_y = 0.0) : fov_x(fov_x), fov_y(fov_y) {}

    bool operator==(const Fov& other) const {
        return fov_x == other.fov_x && fov_y == other.fov_y;
    }
};

struct Frustrum {
    std::array<Normal, 4> normals; // left, right, top, bottom

    Frustrum(Normal normal_left = {}, Normal normal_right = {},
             Normal normal_top = {}, Normal normal_bottom = {})
        : normals({normal_left, normal_right, normal_top, normal_bottom}) {}

    bool operator==(const Frustrum& other) const {
        return normals == other.normals;
    }
};

struct Tile {
    int index;
    Resolution resolution;
    ImagePoint position;
    std::vector<ImagePoint> borders;

    Tile(int index, const Resolution& resolution, const ImagePoint& position,
         const std::vector<ImagePoint>& borders = {})
        : index(index), resolution(resolution), position(position),
          borders(borders) {}
};

using Mat3 = std::array<std::array<double, 3>, 3>;
using Field = std::variant<int, double, std::string>;
enum class Exception { FILE_NOT_FOUND };
using Row = std::vector<Field>;

#endif // TYPES_H
