#ifndef DRAW_HPP
#define DRAW_HPP

#include "projection.hpp"
#include "types.hpp"  // Point3D

class Draw {
 public:
  Draw();

  cv::Mat draw_tile_border(Projection* projection,
                           int tile_id,
                           int lum = 255);
  cv::Mat draw_all_tiles_borders(Projection* projection,
                                 int lum = 255);
  cv::Mat draw_vp_mask(Projection* projection,
                       int lum = 255);
  cv::Mat draw_vp_border(Projection* projection,
                         int lum = 255);
  cv::Mat draw_tiles_seen(Projection* projection,
                          int lum = 255);
  virtual ~Draw() = default;
};

#endif  // DRAW_HPP