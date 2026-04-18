#ifndef SEEN_TILES_H
#define SEEN_TILES_H

#include "projection.hpp"
#include "types.hpp"
#include <vector>

class SeenTiles {
  Fov fov;
  const Projection *projection;
  Tiling tiling;
  Resolution resolution;
  Frustrum default_frustrum;
  Frustrum rotated_frustrum;

  PointYawPitchRoll yaw_pitch_roll;
  
  void set_normals_default();
  bool tile_is_in_frustrum(Tile tile);
  bool is_in(Point3D xyz);
  void rotate_frustrum();
  
  public:
  SeenTiles(const Fov &fov, const Projection *projection);
  std::vector<Tile> get_vptiles(PointYawPitchRoll yaw_pitch_roll);
};

#endif
