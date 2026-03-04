#include "erp.hpp"

Point3D ERP::mn2xyz(const ImagePoint &mn) const
{
    UvPoint uv = this->mn2uv(mn);
    AePoint ae = this->uv2ae(uv);
    Point3D xyz = this->ae2xyz(ae);
    return xyz;
};

UvPoint ERP::mn2uv(const ImagePoint &mn) const
{
    UvPoint uv;
    uv.u = (mn.m + 0.5) / this->resolution.w;
    uv.v = (mn.n + 0.5) / this->resolution.h;
    return uv;
};

AePoint ERP::uv2ae(const UvPoint &uv) const
{
    AePoint ae(0., 0.);
    ae.elevation = uv.v * (-PI) + PI_2;
    ae.azimuth = uv.u * (2 * PI) - PI;
    return ae;
};

Point3D ERP::ae2xyz(const AePoint &ae) const
{
    // Convert from a horizontal coordinate system in radians to a cartesian system.
    // ISO/IEC JTC1/SC29/WG11/N17197l: Algorithm descriptions of projection format conversion and video quality metrics in
    // 360Lib Version 5

    Point3D xyz(0., 0., 0.);
    xyz.x = cos(ae.azimuth) * sin(ae.elevation);
    xyz.y = -sin(ae.azimuth);
    xyz.z = cos(ae.azimuth) * cos(ae.elevation);
    return xyz;
};
