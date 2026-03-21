#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cmath>
#include <numbers>  // pi
#include <numeric>  // std::iota
#include <opencv2/opencv.hpp>
#include <vector>
#include "projection.hpp"  // Projection
#include "types.hpp"       // Point3D

class Viewport {
 private:
  GridPoint3D xyz_grid_default;
  GridPoint3D xyz_grid_rotated;
  PointYawPitchRoll yaw_pitch_roll;

  void fill_xyz_grid_default();
  void rotate_viewport();

 public:
  const Resolution resolution;
  const Fov fov;
  const Projection* projection;

  Viewport(const Resolution& resolution,
           const Fov& fov,
           const Projection* projection);

  cv::Mat extract_viewport(cv::Mat proj_frame,
                           PointYawPitchRoll yaw_pitch_roll);
};

#endif  // VIEWPORT_H
