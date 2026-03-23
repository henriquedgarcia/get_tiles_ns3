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
}
