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
  std::vector<double> y_axis = linspace(-tan_fov_y_2, tan_fov_y_2, h);

  this->xyz_grid_default = GridPoint3D(h, w);
  this->xyz_grid_rotated = this->xyz_grid_default.clone();

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      Point3D xyz_coord(z_axis[j], y_axis[i], 1.0);
      Point3D xyz_coord_normalized = xyz_coord / cv::norm(xyz_coord);
      this->xyz_grid_default(i, j) = xyz_coord_normalized;
    }
  }
}

cv::Mat Viewport::extract_viewport(cv::Mat proj_frame,
                                   PointYawPitchRoll yaw_pitch_roll) {
  cv::Size projection_size = cv::Size(to_int(this->projection.resolution[0]),
                                      to_int(this->projection.resolution[1]));

  if (projection_size != proj_frame.size()) {
    std::cerr << "Input frame shape does not match projection shape."
              << "Resizing input." << std::endl;
    cv::resize(proj_frame, proj_frame, projection_size, 0, 0, cv::INTER_LINEAR);
  }

  rotate_grid(this->xyz_grid_default, yaw_pitch_roll, this->xyz_grid_rotated);

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
  cv::remap(proj_frame,
            vp_img,
            map_x,
            map_y,
            cv::INTER_LINEAR,
            cv::BORDER_WRAP);

  return vp_img;
}
