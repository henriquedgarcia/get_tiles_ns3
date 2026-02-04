#ifndef PROJECTION_H
#define PROJECTION_H

#include <string>
#include <vector>

#include "types.h"

class Projection
{
public:
    Projection(const Resolution &resolution, const Tiling &tiling);
    std::vector<Tile> tile_list;
    Resolution resolution;
    Resolution tile_resolution;
    Tiling tiling;
    int n_tiles;

    std::vector<Tile> make_tile_list();
    std::vector<ImagePoint> get_tile_borders(const Tile &tile);
    
    virtual Point3D mn2xyz(const ImagePoint &mn) const = 0;
};

#endif // PROJECTION_H
