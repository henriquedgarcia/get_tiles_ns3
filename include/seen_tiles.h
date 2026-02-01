#ifndef SEEN_TILES_H
#define SEEN_TILES_H

#include <array>
#include <tuple>
#include <string>
#include "types.h"

using namespace std;

class SeenTiles {
    private:
        Fov fov;
        Tiling tiling;
        const Projection *projection;
        Resolution resolution;
        Frustrum default_frustrum;
        
        Normal normals_default;
        Normal normals_rotated;
        ViewportCoord vp_coord;
        int n_tiles;
        
    public:
        SeenTiles(const Fov &fov, const Projection *projection);
        vector<Tile> get_vptiles(ViewportCoord vp_coord);
};

#endif
