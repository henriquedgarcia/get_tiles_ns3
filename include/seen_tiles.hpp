#ifndef SEEN_TILES_H
#define SEEN_TILES_H

#include <vector>
#include "types.hpp"
#include "projection.hpp"

class SeenTiles {
    private:
        Fov fov;
        const Projection *projection;
        Tiling tiling;
        Resolution resolution;
        Frustrum default_frustrum;
        Frustrum rotated_frustrum;
        
        YawPitchRoll yaw_pitch_roll;
        int n_tiles;

        void set_normals_default();
        bool tile_is_in_frustrum(Tile tile);
        bool is_in(Point3D xyz);

        
    public:
        SeenTiles(const Fov &fov, const Projection *projection);
        std::vector<Tile> get_vptiles(YawPitchRoll yaw_pitch_roll);

};

#endif
