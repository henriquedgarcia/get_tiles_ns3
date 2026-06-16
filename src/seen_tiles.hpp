#ifndef SEEN_TILES_H
#define SEEN_TILES_H

#include "projection.hpp"
#include "types.hpp"
#include <opencv2/core/quaternion.hpp>
#include <vector>

class SeenTiles {
 public:
  Fov fov;
  Projection &projection;
  SeenTiles(const Fov &, Projection &);
  std::vector<Tile> get_vptiles(PointYawPitchRoll);

 private:
  Tiling tiling;
  Resolution resolution;
  Frustrum default_frustrum;
  Frustrum rotated_frustrum;

  void set_normals_default();
  bool tile_is_in_frustrum(Tile tile);
  bool is_in(Point3D xyz);
  void rotate_frustrum(cv::Quatd quat);
};

#endif
