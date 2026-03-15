#include "mat_rot.hpp"

#include <opencv2/core.hpp>
#include <ranges>

#include "types.hpp"

namespace MatRot {

cv::Mat get_matrix(YawPitchRoll yaw_pitch_roll) {
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

  cv::Mat mat_x = (cv::Mat_<double>(3, 3) << 1, 0, 0, 0, cos_pitch, -sin_pitch, 0, sin_pitch, cos_pitch);
  cv::Mat mat_y = (cv::Mat_<double>(3, 3) << cos_yaw, 0, sin_yaw, 0, 1, 0, -sin_yaw, 0, cos_yaw);
  cv::Mat mat_z = (cv::Mat_<double>(3, 3) << cos_roll, -sin_roll, 0, sin_roll, cos_roll, 0, 0, 0, 1);

  return mat_z * mat_y * mat_x;
}

}  // namespace MatRot