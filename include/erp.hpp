#ifndef ERP_H
#define ERP_H

#include "projection.hpp"

class ERP : public Projection {
 public:
  using Projection::Projection;
  Point3D mn2xyz(const PointMN &mn) const override;
  PointMN xyz2mn(const Point3D &xyz) const override;
};

#endif // ERP_H