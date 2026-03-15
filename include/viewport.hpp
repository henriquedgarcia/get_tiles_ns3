#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cmath>
#include <numbers>  // pi
#include <numeric>  // std::iota
#include <opencv2/opencv.hpp>
#include <vector>

#include "projection.hpp"  // Projection
#include "types.hpp"       // Point3D

class Imagem;

// class GnomonicProjection : public Projection {
//  public:
//   Point3D mn2xyz(const ImagePoint& mn) const override;
//   // ImagePoint xyz2mn(const Point3D &xyz) const override;
// };

class Viewport {
 private:
  cv::Mat xyz_grid_default;
  cv::Mat xyz_grid_rotated;
  PointYawPitchRoll yaw_pitch_roll;

  void fill_xyz_grid_default();

 public:
  const Resolution resolution;
  const Fov fov;
  const Projection* projection;

  Viewport(const Resolution& resolution,
           const Fov& fov,
           const Projection* projection);

  cv::Mat extract_viewport(cv::Mat proj_frame, PointYawPitchRoll yaw_pitch_roll);
};

#endif  // VIEWPORT_H
