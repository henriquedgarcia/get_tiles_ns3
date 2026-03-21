#include "viewport.hpp"
#include <opencv2/core/quaternion.hpp>
#include "types.hpp"
#include "utils.hpp"

Viewport::Viewport(const Resolution& resolution,
                   const Fov& fov,
                   const Projection* projection)
    : resolution(resolution),
      fov(fov),
      projection(projection) {
  this->yaw_pitch_roll = {0., 0., 0.};
  this->fill_xyz_grid_default();
}

void Viewport::fill_xyz_grid_default() {
  int w = this->resolution[0];
  int h = this->resolution[1];

  double tan_fov_y_2 = std::tan(this->fov[1] / 2);
  double tan_fov_x_2 = std::tan(this->fov[0] / 2);

  std::vector<double> y_axis = linspace(-tan_fov_y_2, tan_fov_y_2, h);
  std::vector<double> x_axis = linspace(-tan_fov_x_2, tan_fov_x_2, w);

  this->xyz_grid_default = GridPoint3D(h, w);

  for (auto& y : y_axis) {
    for (auto& x : x_axis) {
      Point3D xyz_coord(x, y, 1.0);
      Point3D xyz_coord_normalized = xyz_coord / cv::norm(xyz_coord);
      this->xyz_grid_default(y, x) = xyz_coord_normalized;
    }
  }
}

void Viewport::rotate_viewport() {
  // need yaw_pitch_roll and xyz_grid_default
  this->xyz_grid_rotated = this->xyz_grid_default.clone();
  int rows               = this->xyz_grid_default.rows;
  int cols               = this->xyz_grid_default.cols;

  cv::Quatd q1 = cv::Quatd::createFromAngleAxis(this->yaw_pitch_roll[0],
                                                AXIS_X);  // x
  cv::Quatd q2 = cv::Quatd::createFromAngleAxis(this->yaw_pitch_roll[1],
                                                AXIS_Y);  // y
  cv::Quatd q3 = cv::Quatd::createFromAngleAxis(this->yaw_pitch_roll[2],
                                                AXIS_Z);  // z

  cv::Quatd quat_final = q3 * q1 * q2;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cv::Quatd q_vector           = cv::Quatd(0,
                                     this->xyz_grid_default(i, j)[0],
                                     this->xyz_grid_default(i, j)[1],
                                     this->xyz_grid_default(i, j)[2]);
      cv::Quatd q_conjugate        = quat_final.conjugate();
      cv::Quatd result             = quat_final * q_vector * q_conjugate;
      this->xyz_grid_rotated(i, j) = cv::Vec3d(result.x, result.y, result.z);
    }
  }
}

cv::Mat Viewport::extract_viewport(cv::Mat proj_frame,
                                   PointYawPitchRoll yaw_pitch_roll) {
  Resolution proj_frame_res(proj_frame.cols, proj_frame.rows);
  if (!(proj_frame_res == this->projection->resolution)) {
    throw std::invalid_argument(
        "Input frame shape does not match projection shape");
  }

  this->yaw_pitch_roll = yaw_pitch_roll;
  this->rotate_viewport();

  GridPointMN mn_coord(this->xyz_grid_rotated.rows,
                       this->xyz_grid_rotated.cols);

  for (int i = 0; i < this->xyz_grid_rotated.rows; i++) {
    for (int j = 0; j < this->xyz_grid_rotated.cols; j++) {
      mn_coord(i, j) = this->projection->xyz2mn(this->xyz_grid_rotated(i, j));
    }
  }

  cv::Mat map1, map2;
  mn_coord.col(1).convertTo(map1, CV_64F);  // mapa do X
  mn_coord.col(0).convertTo(map2, CV_64F);  // mapa do Y

  cv::Mat vp_img;
  cv::remap(proj_frame, vp_img, map1, map2, cv::INTER_LINEAR, cv::BORDER_WRAP);

  return vp_img;
}
