#include "viewport.hpp"
// #include "mat_rot.hpp"
#include "types.hpp"
#include "utils.hpp"

Viewport::Viewport(const Resolution& resolution, const Fov& fov, const Projection* projection)
    : resolution(resolution), fov(fov), projection(projection) {
  this->yaw_pitch_roll = {0., 0., 0.};
  this->fill_xyz_grid_default();
}

void Viewport::fill_xyz_grid_default() {
  double tan_fov_y_2 = std::tan(this->fov[1] / 2);
  double tan_fov_x_2 = std::tan(this->fov[0] / 2);
  int w = this->resolution[0];
  int h = this->resolution[1];

  cv::Mat y_axis = linspace(-tan_fov_y_2, tan_fov_y_2, h);
  cv::Mat x_axis = linspace(-tan_fov_x_2, tan_fov_x_2, w);

  this->xyz_grid_default = cv::Mat(h, w, CV_64FC3);
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      cv::Vec3d xyz_coord(x_axis.at<double>(0, i), y_axis.at<double>(0, j), 1.0);
      cv::Vec3d xyz_coord_normalized = xyz_coord / cv::norm(xyz_coord);
      this->xyz_grid_default.at<cv::Vec3d>(j, i) = xyz_coord_normalized;
    }
  }
}
// cv::Mat Viewport::rotate_viewport() {
//   this->rotated_frustrum = rotate_frustrum(this->default_frustrum, matrot);
// }

// cv::Mat Viewport::extract_viewport(cv::Mat proj_frame,
//                                    ViewportCoord yaw_pitch_roll) {
//   this->yaw_pitch_roll = yaw_pitch_roll;
//   cv::Mat result = proj_frame.clone();
//   Resolution proj_frame_res(proj_frame.cols, proj_frame.rows);

//   if (!(proj_frame_res == this->projection->resolution)) {
//     throw std::invalid_argument(
//         "Input frame shape does not match projection shape");
//   }

//   PointMN nm_coord = this->projection->xyz2mn(this->xyz_grid_default);
//   Mat3 matrot = get_matrix(this->yaw_pitch_roll);
//   cv::Mat rotated_xyz = applyRotation(this->xyz_grid_default, matrot);
//   // Extrai colunas equivalentes ao slicing Python
//   cv::Mat map1, map2;
//   nm_coord.col(1).convertTo(map1, CV_64F);
//   nm_coord.col(0).convertTo(map2, CV_64F);

//   cv::Mat vp_img;
//   cv::remap(proj_frame, vp_img, map1, map2, cv::INTER_LINEAR, cv::BORDER_WRAP);

//   return vp_img;

//   /*
//     if tuple(proj_frame.shape)[:2] != tuple(self.projection.shape)[:2]:
//         raise ValueError(f"Input frame shape {tuple(proj_frame.shape)[:2]} does
//     not match projection shape {tuple(self.projection.shape)[:2]}")

//     if self.projection is None:
//       raise ProjectionError('Projection is not defined.')

//       if yaw_pitch_roll is not None:
//         self.yaw_pitch_roll = yaw_pitch_roll

//     nm_coord = self.projection.xyz2nm(self.xyz)
//     nm_coord = nm_coord.transpose((1, 2, 0))
//     vp_img = cv2.remap(proj_frame, map1=nm_coord[..., 1:2].astype(np.float32),
//                         map2=nm_coord[..., 0:1].astype(np.float32),
//     interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_WRAP) # show(vp_img)
//     return vp_img
//   */
//   return result;
// }
