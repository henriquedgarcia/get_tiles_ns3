#include "mat_rot.h"
#include "types.h"
#include <ranges>

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

        double cos_yaw = cos(yaw_pitch_roll.yaw);
        double cos_pitch = cos(yaw_pitch_roll.pitch);
        double cos_roll = cos(yaw_pitch_roll.roll);
        double sin_yaw = sin(yaw_pitch_roll.yaw);
        double sin_pitch = sin(yaw_pitch_roll.pitch);
        double sin_roll = sin(yaw_pitch_roll.roll);

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

} // namespace MatRot