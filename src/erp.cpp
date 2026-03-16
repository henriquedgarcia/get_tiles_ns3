#include "erp.hpp"

#include <opencv2/core.hpp>
///////////////////// 2D to 3D conversions /////////////////////

Point3D ERP::mn2xyz(const PointMN& mn) const {
  PointUV uv = this->mn2uv(mn);
  AePoint ae = this->uv2ae(uv);
  Point3D xyz = this->ae2xyz(ae);
  return xyz;
};

PointUV ERP::mn2uv(const PointMN& mn) const {
  PointUV uv;
  uv[0] = (mn[0] + 0.5) / this->resolution[0];
  uv[1] = (mn[1] + 0.5) / this->resolution[1];
  return uv;
};

AePoint ERP::uv2ae(const PointUV& uv) const {
  AePoint ae(0., 0.);
  ae[0] = uv[1] * (-PI) + PI_2;
  ae[1] = uv[0] * (2 * PI) - PI;
  return ae;
};

Point3D ERP::ae2xyz(const AePoint& ae) const {
  // Convert from a horizontal coordinate system in radians to a cartesian
  // system. ISO/IEC JTC1/SC29/WG11/N17197l: Algorithm descriptions of
  // projection format conversion and video quality metrics in 360Lib Version 5

  Point3D xyz(0., 0., 0.);
  xyz[0] = cos(ae[0]) * sin(ae[1]);
  xyz[1] = -sin(ae[0]);
  xyz[2] = cos(ae[0]) * cos(ae[1]);
  return xyz;
};

///////////////////// 3D to 2D conversions /////////////////////
PointMN ERP::xyz2mn(const Point3D& xyz) const {
  AePoint ae = this->xyz2ae(xyz);
  PointUV uv = this->ae2uv(ae);
  PointMN mn = this->uv2mn(uv);
  return mn;
};

AePoint ERP::xyz2ae(const Point3D& xyz) const {
  cv::Vec3d vec_xyz(xyz[0], xyz[1], xyz[2]);

  double r = cv::norm(vec_xyz);
  double elevation = asin(xyz[1] / r);
  double azimuth = atan2(-xyz[0], -xyz[2]);
  azimuth = fmod(azimuth + CV_PI, 2 * CV_PI) - CV_PI;
  return AePoint(azimuth, elevation);
};

PointUV ERP::ae2uv(const AePoint& ae) const {
  double u = -ae[1] / PI + 0.5;
  double v = ae[0] / (2 * PI) + 0.5;
  return PointUV(u, v);
};

PointMN ERP::uv2mn(const PointUV& uv) const {
  unsigned short int w = this->resolution[0];
  unsigned short int h = this->resolution[1];
  ushort n = uv[1] * (h - 1) + 0.5;
  ushort m = uv[0] * (w - 1) + 0.5;
  return PointMN(m, n);
};
