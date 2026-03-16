#ifndef ERP_H
#define ERP_H

#include "projection.hpp"

class ERP : public Projection {
 public:
  using Projection::Projection;
  Point3D mn2xyz(const PointMN& mn) const override;
  PointMN xyz2mn(const Point3D& xyz) const override;

  PointUV mn2uv(const PointMN& mn) const;
  AePoint uv2ae(const PointUV& uv) const;
  Point3D ae2xyz(const AePoint& ae) const;
  // todo: add uv2mn, ae2uv, xyz2ae
  AePoint xyz2ae(const Point3D& xyz) const;
  PointUV ae2uv(const AePoint& ae) const;
  PointMN uv2mn(const PointUV& uv) const;
};

#endif  // ERP_H