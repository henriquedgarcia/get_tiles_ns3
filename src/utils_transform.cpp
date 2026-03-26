#include "projection.hpp"
#include "types.hpp"
#include <iostream>
#include <opencv2/core/quaternion.hpp>

GridPoint3D applyRotation(const GridPoint3D xyz_grid_default,
                          const cv::Quatd quat) {
  int rows = xyz_grid_default.rows;
  int cols = xyz_grid_default.cols;

  GridPoint3D xyz_grid_rotated = xyz_grid_default.clone();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cv::Quatd q_vector =
          cv::Quatd(0, xyz_grid_default(i, j)[0], xyz_grid_default(i, j)[1],
                    xyz_grid_default(i, j)[2]);
      cv::Quatd quat_conjugate = quat.conjugate();
      cv::Quatd result = quat * q_vector * quat_conjugate;
      xyz_grid_rotated(i, j) = cv::Vec3d(result.x, result.y, result.z);
    }
  }

  return xyz_grid_rotated;
}
