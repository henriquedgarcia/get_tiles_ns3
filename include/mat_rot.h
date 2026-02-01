#ifndef MAT_ROT_H
#define MAT_ROT_H

#include "types.h"

namespace MatRot
{
    Mat3 get_matrix(ViewportCoord yaw_pitch_roll);

    inline Mat3 mult2(const Mat3 &A, const Mat3 &B);

    inline Point3D apply_matrix(const Mat3 &mat, const Point3D &p);

    inline Frustrum rotate_frustrum(Frustrum frustrum, const Mat3 &mat);

} // namespace MatRot

#endif // MAT_ROT_H
