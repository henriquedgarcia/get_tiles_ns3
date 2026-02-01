#include "mat_rot.h"
#include "types.h"

namespace MatRot
{

    Mat3 get_matrix(ViewportCoord yaw_pitch_roll)
    {
        /*
        Create rotation matrix using Tait–Bryan angles in Z-Y-X order.
        See Wikipedia. Use:
            X axis point to right
            Y axis point to down
            Z axis point to front

        Examples
        --------
        >> x, y, z = point
        >> mat = rot_matrix([yaw, pitch, roll])
        >> mat @ (x, y, z)

        :param yaw_pitch_roll: the rotation (yaw, pitch, roll) in rad.
        :return: A 3x3 matrix of rotation
        */

        float cos_yaw = cos(yaw_pitch_roll.yaw);
        float cos_pitch = cos(yaw_pitch_roll.pitch);
        float cos_roll = cos(yaw_pitch_roll.roll);
        float sin_yaw = sin(yaw_pitch_roll.yaw);
        float sin_pitch = sin(yaw_pitch_roll.pitch);
        float sin_roll = sin(yaw_pitch_roll.roll);

        Mat3 mat_x{{{1, 0, 0},
                    {0, cos_pitch, -sin_pitch},
                    {0, sin_pitch, cos_pitch}}};
        Mat3 mat_y{{{cos_yaw, 0, sin_yaw},
                    {0, 1, 0},
                    {-sin_yaw, 0, cos_yaw}}};
        Mat3 mat_z{{{cos_roll, -sin_roll, 0},
                    {sin_roll, cos_roll, 0},
                    {0, 0, 1}}};

        Mat3 mat_zy = mult2(mat_z, mat_y);
        return mult2(mat_zy, mat_x);
    }

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
        float x = mat[0][0] * p.x + mat[0][1] * p.y + mat[0][2] * p.z;
        float y = mat[1][0] * p.x + mat[1][1] * p.y + mat[1][2] * p.z;
        float z = mat[2][0] * p.x + mat[2][1] * p.y + mat[2][2] * p.z;
        return Point3D(x, y, z);
    }

    inline Frustrum rotate_frustrum(Frustrum frustrum, const Mat3 &mat)
    {
        /* Rotate the normals of the frustrum f using matrix M */
        frustrum.normals[0] = apply_matrix(mat, frustrum.normals[0]);
        frustrum.normals[1] = apply_matrix(mat, frustrum.normals[1]);
        frustrum.normals[2] = apply_matrix(mat, frustrum.normals[2]);
        frustrum.normals[3] = apply_matrix(mat, frustrum.normals[3]);
        return frustrum;
    }

} // namespace MatRot