#include "erp.hpp"
#include "coord_map.hpp"
#include <opencv2/core.hpp>

Point3D ERP::mn2xyz(const PointMN &mn) const {
  PointUV uv = erp_space::mn2uv(mn, this->resolution);
  AePoint ae = erp_space::uv2ae(uv);
  Point3D xyz = ae2xyz(ae);
  return xyz;
};

PointMN ERP::xyz2mn(const Point3D &xyz) const {
  AePoint ae = xyz2ae(xyz);
  PointUV uv = erp_space::ae2uv(ae);
  PointMN mn = erp_space::uv2mn(uv, this->resolution);
  return mn;
};
