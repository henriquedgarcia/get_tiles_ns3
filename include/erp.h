#ifndef ERP_H
#define ERP_H

#include "projection.h"

class ERP : public Projection
{
public:
    using Projection::Projection;
    Point3D mn2xyz(const ImagePoint &mn) const override;
    UvPoint mn2uv(const ImagePoint &mn) const;
    AePoint uv2ae(const UvPoint &uv) const;
    Point3D ae2xyz(const AePoint &ae) const;
};

#endif // ERP_H