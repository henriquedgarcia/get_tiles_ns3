#ifndef PROJECTION_H
#define PROJECTION_H

#include "types.hpp"
#include <string>
#include <vector>

class Projection {
public:
  Resolution resolution;
  Tiling tiling;
  Resolution tile_resolution;
  std::vector<Tile> tile_list;
  uchar n_tiles;

  Projection(const Resolution &resolution, const Tiling &tiling);
  virtual ~Projection() = default;

  virtual Point3D mn2xyz(const PointMN &mn) const = 0;
  virtual PointMN xyz2mn(const Point3D &xyz) const = 0;

  std::vector<Tile> get_tile_list();
};

#endif // PROJECTION_H
