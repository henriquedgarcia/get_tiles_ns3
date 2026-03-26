#include "erp_map.hpp"

#include "projection.hpp"

PointUV erp::mn2uv(const PointMN &mn, const Resolution &resolution) {
  double u = (mn[0] + 0.5) / resolution[0];
  double v = (mn[1] + 0.5) / resolution[1];
  return PointUV(u, v);
};

AePoint erp::uv2ae(const PointUV &uv) {
  double a = uv[1] * (-PI) + PI_2;
  double e = uv[0] * (2 * PI) - PI;
  return AePoint(a, e);
}

Point3D erp::ae2xyz(const AePoint &ae) {
  // Convert from a horizontal coordinate system in radians to a cartesian
  // system. ISO/IEC JTC1/SC29/WG11/N17197l: Algorithm descriptions of
  // projection format conversion and video quality metrics in 360Lib Version 5

  double x = cos(ae[0]) * sin(ae[1]);
  double y = -sin(ae[0]);
  double z = cos(ae[0]) * cos(ae[1]);
  return Point3D(x, y, z);
};

AePoint erp::xyz2ae(const Point3D &xyz) {
  cv::Vec3d vec_xyz(xyz[0], xyz[1], xyz[2]);

  double r = cv::norm(vec_xyz);
  double elevation = asin(xyz[1] / r);
  double azimuth = atan2(-xyz[0], -xyz[2]);
  azimuth = fmod(azimuth + CV_PI, 2 * CV_PI) - CV_PI;
  return AePoint(azimuth, elevation);
};

PointUV erp::ae2uv(const AePoint &ae) {
  double u = -ae[1] / PI + 0.5;
  double v = ae[0] / (2 * PI) + 0.5;
  return PointUV(u, v);
};

PointMN erp::uv2mn(const PointUV &uv, const Resolution &resolution) {
  ushort n = uv[1] * (resolution[1] - 1) + 0.5;
  ushort m = uv[0] * (resolution[0] - 1) + 0.5;
  return PointMN(m, n);
};
