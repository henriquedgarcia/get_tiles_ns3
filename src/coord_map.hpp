#include "types.hpp"

Point3D ae2xyz(const AePoint &ae);
AePoint xyz2ae(const Point3D &xyz);

namespace erp_space {
PointUV ae2uv(const AePoint &ae);
AePoint uv2ae(const PointUV &uv);
PointMN uv2mn(const PointUV &uv, const Resolution &resolution);
PointUV mn2uv(const PointMN &mn, const Resolution &resolution);
} // namespace erp_space