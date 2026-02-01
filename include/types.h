#ifndef TYPES_H
#define TYPES_H

#include <array>

using namespace std;

struct ViewportCoord
{
    float yaw;
    float pitch;
    float roll;

    ViewportCoord(float yaw = 0, float pitch = 0, float roll = 0)
        : yaw(yaw), pitch(pitch), roll(roll) {}

    bool operator==(const ViewportCoord &other) const
    {
        return yaw == other.yaw && pitch == other.pitch && roll == other.roll;
    }
};

struct Point3D
{
    float x;
    float y;
    float z;

    Point3D(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z) {}

    bool operator==(const Point3D &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct ImagePoint
{
    int m;
    int n;

    ImagePoint(int m = 0, int n = 0)
        : m(m), n(n) {}

    bool operator==(const ImagePoint &other) const
    {
        return m == other.m && n == other.n;
    }
};

struct Resolution
{
    int w;
    int h;

    Resolution(int w = 0, int h = 0)
        : w(w), h(h) {}

    bool operator==(const Resolution &other) const
    {
        return w == other.w && h == other.h;
    }
};

using Tiling = Resolution;
using Fov = Resolution;
using Normal = Point3D;

struct Frustrum
{
    array<Normal, 4> normals; // left, right, top, bottom

    Frustrum(Normal normal_left, Normal normal_right, Normal normal_top, Normal normal_bottom)
        : normals({normal_left, normal_right, normal_top, normal_bottom}) {}

    Frustrum()
        : normals({Normal(0, 0, 0), Normal(0, 0, 0), Normal(0, 0, 0), Normal(0, 0, 0)}) {}

    bool operator==(const Frustrum &other) const
    {
        return normals[0] == other.normals[0] && normals[1] == other.normals[1] && normals[2] == other.normals[2] && normals[3] == other.normals[3];
    }
};

using Mat3 = std::array<std::array<double, 3>, 3>;

struct Tile
{
    int index;
    Resolution resolution;
    ImagePoint position;
    vector<ImagePoint> borders;

    Tile(int index, Resolution resolution, ImagePoint position)
        : index(index), resolution(resolution), position(position) {};
};

#endif // TYPES_H
