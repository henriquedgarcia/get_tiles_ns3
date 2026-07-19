#include "viewport.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <opencv2/core/quaternion.hpp>

Viewport::Viewport(const Resolution &resolution,
                   const Fov &fov,
                   Projection &projection)
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

  // x: esquerda negativo, direita positivo
  std::vector<double> z_axis = linspace(-tan_fov_x_2, tan_fov_x_2, w);
  // y: topo negativo, baixo positivo
  std::vector<double> y_axis = linspace(tan_fov_y_2, -tan_fov_y_2, h);

  this->xyz_grid_default = GridPoint3D(h, w);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      Point3D xyz_coord(1.0, y_axis[i], z_axis[j]);
      Point3D xyz_coord_normalized = xyz_coord / cv::norm(xyz_coord);
      this->xyz_grid_default(i, j) = xyz_coord_normalized;
    }
  }
}

void Viewport::rotate_viewport() {
  // need yaw_pitch_roll and xyz_grid_default
  this->xyz_grid_rotated = this->xyz_grid_default.clone();
  int rows = this->xyz_grid_default.rows;
  int cols = this->xyz_grid_default.cols;
  double yaw = this->yaw_pitch_roll[0];
  double pitch = this->yaw_pitch_roll[1];
  double roll = this->yaw_pitch_roll[2];

  cv::Quatd qy = cv::Quatd::createFromAngleAxis(yaw, AXIS_Y);
  cv::Quatd qz = cv::Quatd::createFromAngleAxis(pitch, AXIS_Z);
  cv::Quatd qx = cv::Quatd::createFromAngleAxis(roll, AXIS_X);

  cv::Quatd quat_final = qx * qz * qy;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cv::Quatd q_vector = cv::Quatd(0,
                                     this->xyz_grid_default(i, j)[0],
                                     this->xyz_grid_default(i, j)[1],
                                     this->xyz_grid_default(i, j)[2]);
      cv::Quatd q_conjugate = quat_final.conjugate();
      cv::Quatd result = quat_final * q_vector * q_conjugate;
      this->xyz_grid_rotated(i, j) = cv::Vec3d(result.x, result.y, result.z);
    }
  }
}

cv::Mat Viewport::extract_viewport(cv::Mat proj_frame,
                                   PointYawPitchRoll yaw_pitch_roll) {
  Resolution proj_frame_res(proj_frame.cols, proj_frame.rows);

  if (!(proj_frame_res == this->projection.resolution)) {
    throw std::invalid_argument(
        "Input frame shape does not match projection shape");
  }

  this->yaw_pitch_roll = yaw_pitch_roll;
  this->rotate_viewport();

  GridPointMN mn_coord(this->xyz_grid_rotated.rows,
                       this->xyz_grid_rotated.cols);

  for (int i = 0; i < this->xyz_grid_rotated.rows; i++) {
    for (int j = 0; j < this->xyz_grid_rotated.cols; j++) {
      mn_coord(i, j) = this->projection.xyz2mn(this->xyz_grid_rotated(i, j));
    }
  }

  std::vector<cv::Mat> channels;
  cv::split(mn_coord, channels); // channels[0]=m (x), channels[1]=n (y)

  cv::Mat map_x, map_y;
  channels[0].convertTo(map_x, CV_32F); // mapa do X
  channels[1].convertTo(map_y, CV_32F); // mapa do Y

  cv::Mat vp_img;
  cv::remap(proj_frame, vp_img, map_x, map_y, cv::INTER_LINEAR, cv::BORDER_WRAP);

  return vp_img;
}
