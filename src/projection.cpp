#include "projection.hpp"
#include "types.hpp"
#include "utils.hpp"

Projection::Projection(const Resolution& resolution,
                       const Tiling& tiling)
    : resolution(resolution),
      tiling(tiling),
      n_tiles(tiling[0] * tiling[1]),
      tile_resolution(resolution[0] / tiling[0],
                      resolution[1] / tiling[1]) {
                        this->tile_list = make_tile_list(this);
                      }
