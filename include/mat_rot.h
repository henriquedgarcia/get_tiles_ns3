#ifndef MAT_ROT_H
#define MAT_ROT_H

#include "types.h"

namespace MatRot
{
    Mat3 get_matrix(ViewportCoord yaw_pitch_roll);

    inline Mat3 mult2(const Mat3 &A, const Mat3 &B)
    {
        /* Multiply two 3x3 matrices A and B */
        Mat3 C{};
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j];
            }
        }
        return C;
    }

    inline Point3D apply_matrix(const Mat3 &mat, const Point3D &p)
    {
        /* Apply matrix M to point p */
        Point3D xyz;
        xyz.x = mat[0][0] * p.x + mat[0][1] * p.y + mat[0][2] * p.z;
        xyz.y = mat[1][0] * p.x + mat[1][1] * p.y + mat[1][2] * p.z;
        xyz.z = mat[2][0] * p.x + mat[2][1] * p.y + mat[2][2] * p.z;
        return xyz;
    }

    inline Frustrum rotate_frustrum(const Frustrum &frustrum, const Mat3 &mat)
    {
        Frustrum rotated = frustrum;
        for (auto &normal : rotated.normals)
        {
            normal = apply_matrix(mat, normal);
        }

        return rotated;
    }

} // namespace MatRot

#endif // MAT_ROT_H
