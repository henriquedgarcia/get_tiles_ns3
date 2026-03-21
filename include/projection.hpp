#ifndef PROJECTION_H
#define PROJECTION_H

#include <string>
#include <vector>
#include "types.hpp"

class Projection {
 public:
  std::vector<Tile> tile_list;
  Resolution resolution;
  Tiling tiling;
  Resolution tile_resolution;
  uchar n_tiles;

  Projection(const Resolution& resolution,
             const Tiling& tiling);

  virtual Point3D mn2xyz(const PointMN& mn) const  = 0;
  virtual PointMN xyz2mn(const Point3D& xyz) const = 0;
  virtual ~Projection()                            = default;

 protected:
  void make_tile_list();
  static std::vector<PointMN> get_tile_borders(const Tile& tile);
};

#endif  // PROJECTION_H
