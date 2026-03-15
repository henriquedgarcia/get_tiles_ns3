#ifndef ERP_H
#define ERP_H

#include "projection.hpp"

class ERP : public Projection {
 public:
  using Projection::Projection;
  Point3D mn2xyz(const ImagePoint& mn) const override;
  ImagePoint xyz2mn(const Point3D& xyz) const override;

  UvPoint mn2uv(const ImagePoint& mn) const;
  AePoint uv2ae(const UvPoint& uv) const;
  Point3D ae2xyz(const AePoint& ae) const;
  // todo: add uv2mn, ae2uv, xyz2ae
  AePoint xyz2ae(const Point3D& xyz) const;
  UvPoint ae2uv(const AePoint& ae) const;
  ImagePoint uv2mn(const UvPoint& uv) const;
};

#endif  // ERP_H