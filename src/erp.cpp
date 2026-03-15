#include "erp.hpp"
#include <opencv2/core.hpp>
///////////////////// 2D to 3D conversions /////////////////////

Point3D ERP::mn2xyz(const ImagePoint& mn) const {
  PointUV uv = this->mn2uv(mn);
  AePoint ae = this->uv2ae(uv);
  Point3D xyz = this->ae2xyz(ae);
  return xyz;
};

PointUV ERP::mn2uv(const ImagePoint& mn) const {
  PointUV uv;
  uv[0] = (mn.m + 0.5) / this->resolution.w;
  uv[1] = (mn.n + 0.5) / this->resolution.h;
  return uv;
};

AePoint ERP::uv2ae(const PointUV& uv) const {
  AePoint ae(0., 0.);
  ae.elevation = uv[1] * (-PI) + PI_2;
  ae.azimuth = uv[0] * (2 * PI) - PI;
  return ae;
};

Point3D ERP::ae2xyz(const AePoint& ae) const {
  // Convert from a horizontal coordinate system in radians to a cartesian
  // system. ISO/IEC JTC1/SC29/WG11/N17197l: Algorithm descriptions of
  // projection format conversion and video quality metrics in 360Lib Version 5

  Point3D xyz(0., 0., 0.);
  xyz.x = cos(ae.azimuth) * sin(ae.elevation);
  xyz.y = -sin(ae.azimuth);
  xyz.z = cos(ae.azimuth) * cos(ae.elevation);
  return xyz;
};

///////////////////// 3D to 2D conversions /////////////////////
ImagePoint ERP::xyz2mn(const Point3D& xyz) const {
  AePoint ae = this->xyz2ae(xyz);
  PointUV uv = this->ae2uv(ae);
  ImagePoint mn = this->uv2mn(uv);
  return mn;
};

AePoint ERP::xyz2ae(const Point3D& xyz) const {
  cv::Vec3d vec_xyz(xyz.x, xyz.y, xyz.z);

  double r = cv::norm(vec_xyz);
  double elevation = asin(xyz.y / r);
  double azimuth = atan2(-xyz.x, -xyz.z);
  azimuth = fmod(azimuth + CV_PI, 2 * CV_PI) - CV_PI;
  return AePoint(azimuth, elevation);
};

PointUV ERP::ae2uv(const AePoint& ae) const {
  double u = -ae.elevation / PI + 0.5;
  double v = ae.azimuth / (2 * PI) + 0.5;
  return PointUV(u, v);
};

ImagePoint ERP::uv2mn(const PointUV& uv) const {
  auto [w, h] = this->resolution;
  int n = uv[1] * (h - 1) + 0.5;
  int m = uv[0] * (w - 1) + 0.5;
  return ImagePoint(m, n);
};
