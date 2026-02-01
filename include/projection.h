#ifndef PROJECTION_H
#define PROJECTION_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

class Projection
{
protected:
    int n_tiles;

public:
    vector<Tile> tile_list;
    Resolution resolution;
    Resolution tile_resolution;
    Tiling tiling;

    virtual Point3D nm2xyz(const ImagePoint &nm) const = 0;
    virtual ImagePoint xyz2nm(const Point3D &xyz) const = 0;

    Projection(const Resolution &resolution, const Tiling &tiling);
    vector<Tile> make_tile_list();
    vector<ImagePoint> get_tile_borders(const Tile &tile);
};

#endif // PROJECTION_H
