#include "projection.hpp"
#include <vector>
#include "types.hpp"

using namespace std;

Projection::Projection(const Resolution& resolution,
                       const Tiling& tiling)
    : resolution(resolution),
      tiling(tiling) {
  this->n_tiles         = tiling[0] * tiling[1];
  int tile_w            = resolution[0] / tiling[0];
  int tile_h            = resolution[1] / tiling[1];
  this->tile_resolution = Resolution(tile_w, tile_h);

  this->make_tile_list();
}

void Projection::make_tile_list() {
  int index = 0;
  vector<Tile> vptiles;

  for (int h = 0; h < this->tiling[1]; h++) {
    for (int w = 0; w < this->tiling[0]; w++) {
      PointMN position(w * (this->tile_resolution[0]),
                       h * (this->tile_resolution[1]));
      Tile tile(index, this->tile_resolution, position);
      tile.borders = this->get_tile_borders(tile);
    
      vector<Point3D> xyz_points;
      for(const auto& border : tile.borders) {
        xyz_points.push_back(this->mn2xyz(border));
      } 
      tile.borders_xyz = xyz_points;

      vptiles.push_back(tile);
      index++;
    }
  }
  this->tile_list = vptiles;
}

vector<PointMN> Projection::get_tile_borders(const Tile& tile) {
  vector<PointMN> borders;

  int left_x   = tile.position[0];
  int right_x  = tile.position[0] + tile.resolution[0];
  int top_y    = tile.position[1];
  int bottom_y = tile.position[1] + tile.resolution[1];

  for (int x = left_x; x < right_x; x++) {
    borders.push_back(PointMN(x, top_y));     // Top edge
    borders.push_back(PointMN(x, bottom_y));  // Bottom edge
  }
  for (int y = top_y; y < bottom_y; y++) {
    borders.push_back(PointMN(left_x, y));   // Left edge
    borders.push_back(PointMN(right_x, y));  // Right edge
  }

  return borders;
};
