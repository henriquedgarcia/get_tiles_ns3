#include "seen_tiles.hpp"
#include "mat_rot.hpp"
#include "projection.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <array>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace MatRot;

SeenTiles::SeenTiles(const Fov& fov, const Projection* projection) {
    this->fov = fov;
    this->projection = projection;
    this->tiling = projection->tiling;
    this->resolution = projection->resolution;
    this->n_tiles = tiling.w * tiling.h;

    this->set_normals_default();
}

void SeenTiles::set_normals_default() {
    double fov_w_2 = this->fov.fov_x / 2;
    double fov_h_2 = this->fov.fov_y / 2;
    double cos_fov_w = cos(fov_w_2);
    double cos_fov_h = cos(fov_h_2);
    double sin_fov_w = sin(fov_w_2);
    double sin_fov_h = sin(fov_h_2);

    // (x, y, z)
    Frustrum frustrum(Normal(-cos_fov_w, 0.0f, -sin_fov_w), // left
                      Normal(cos_fov_w, 0.0f, -sin_fov_w),  // right
                      Normal(0.0f, -cos_fov_h, -sin_fov_h), // top
                      Normal(0.0f, cos_fov_h, -sin_fov_h)   // bottom
    );
    this->default_frustrum = frustrum;
}

vector<Tile> SeenTiles::get_vptiles(YawPitchRoll yaw_pitch_roll) {
    this->yaw_pitch_roll = yaw_pitch_roll;
    vector<Tile> vptiles;

    // Se o tiling é 1x1 retorne logo o único tile.
    if (this->tiling == Tiling(1, 1)) {
        vptiles.push_back(this->projection->tile_list[0]);
        return vptiles;
    }

    // Mat3 matrot = get_matrix(yaw_pitch_roll);
    // this->rotated_frustrum = rotate_frustrum(this->default_frustrum, matrot);

    for (const Tile& tile : this->projection->tile_list) {
        if (tile_is_in_frustrum(tile)) {
            vptiles.push_back(tile);
        }
    }
    return vptiles;
}

bool SeenTiles::tile_is_in_frustrum(Tile tile) {
    /* Um tile está no frustrum se pelo menos um ponto estiver dentro do
     * frustrum */
    for (const ImagePoint& point : tile.borders) {
        Point3D xyz = this->projection->mn2xyz(point);
        if (this->is_in(xyz)) {
            return true;
        }
    }
    return false;
}

bool SeenTiles::is_in(Point3D xyz) {
    /* um ponto está dentro do frustrum se todos os produtos forem menores que
     * zero */
    for (const Normal& normal : this->rotated_frustrum.normals) {
        double prod = dot(normal, xyz);
        if (prod > 0) {
            return false;
        }
    }
    return true;
}
