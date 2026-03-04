#ifndef SEEN_TILES_H
#define SEEN_TILES_H

#include <vector>
#include "types.h"
#include "projection.h"

class SeenTiles {
    private:
        Fov fov;
        const Projection *projection;
        Tiling tiling;
        Resolution resolution;
        Frustrum default_frustrum;
        
        Normal normals_default;
        Normal normals_rotated;
        ViewportCoord vp_coord;
        int n_tiles;
        
    public:
        SeenTiles(const Fov &fov, const Projection *projection);
        std::vector<Tile> get_vptiles(ViewportCoord vp_coord);

};

#endif
