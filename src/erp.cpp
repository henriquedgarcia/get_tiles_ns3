#include "erp.hpp"
#include <opencv2/core.hpp>
///////////////////// 2D to 3D conversions /////////////////////

Point3D ERP::mn2xyz(const ImagePoint& mn) const {
  UvPoint uv = this->mn2uv(mn);
  AePoint ae = this->uv2ae(uv);
  Point3D xyz = this->ae2xyz(ae);
  return xyz;
};

UvPoint ERP::mn2uv(const ImagePoint& mn) const {
  UvPoint uv;
  uv.u = (mn.m + 0.5) / this->resolution.w;
  uv.v = (mn.n + 0.5) / this->resolution.h;
  return uv;
};

AePoint ERP::uv2ae(const UvPoint& uv) const {
  AePoint ae(0., 0.);
  ae.elevation = uv.v * (-PI) + PI_2;
  ae.azimuth = uv.u * (2 * PI) - PI;
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
  UvPoint uv = this->ae2uv(ae);
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

UvPoint ERP::ae2uv(const AePoint& ae) const {
  double u = -ae.elevation / PI + 0.5;
  double v = ae.azimuth / (2 * PI) + 0.5;
  return UvPoint(u, v);
};

ImagePoint ERP::uv2mn(const UvPoint& uv) const {
  auto [w, h] = this->resolution;
  int n = uv.v * (h - 1) + 0.5;
  int m = uv.u * (w - 1) + 0.5;
  return ImagePoint(m, n);
};
