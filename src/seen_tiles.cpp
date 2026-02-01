#include "mat_rot.h"
#include "seen_tiles.h"
#include "types.h"
#include "projection.h"

#include <array>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

SeenTiles::SeenTiles(const Fov &fov, const Projection *projection)
    : projection(projection), fov(fov)
{
    this->tiling = projection->tiling;
    this->resolution = projection->resolution;
    this->n_tiles = tiling.w * tiling.h;

    float fov_w_2 = fov.w / 2;
    float fov_h_2 = fov.h / 2;
    float cos_fov_w = cos(fov_w_2);
    float cos_fov_h = cos(fov_h_2);
    float sin_fov_w = sin(fov_w_2);
    float sin_fov_h = sin(fov_h_2);

    // (x, y, z)
    Frustrum frustrum(
        Normal(-cos_fov_w, 0.0f, -sin_fov_w), // left
        Normal(cos_fov_w, 0.0f, -sin_fov_w),  // right
        Normal(0.0f, -cos_fov_h, -sin_fov_h), // top
        Normal(0.0f, cos_fov_h, -sin_fov_h)   // bottom
    );
    this->default_frustrum = frustrum;
}

vector<Tile> SeenTiles::get_vptiles(ViewportCoord vp_coord)
{
    this->vp_coord = vp_coord;
    Mat3 matrot = MatRot::get_matrix(vp_coord);
    Frustrum frustrum_rotated = MatRot::rotate_frustrum(this->default_frustrum, matrot);

    vector<Tile> vptiles;

    for (int i = 0; i < this->n_tiles; ++i)
    {
        if (this->tiling == Tiling(1, 1))
        {
            Tile tile(i, this->resolution, ImagePoint(0, 0));
            vptiles.push_back(tile);
            continue;
        }
    }

    for (const Tile &tile : this->projection->tile_list)
    {
        bool inside = true;
        // para cada ponto da borda do tile
        for (const ImagePoint &point : tile.borders)
        {
            // converter para 3D
            Point3D xyz = this->projection->nm2xyz(point);
            // Para cada normal do frustrum_rotated
            for (const Normal &normal : frustrum_rotated.normals)
            {
                // fazer o produto vetorial com todas as normais
                float prod = normal.x * xyz.x + normal.y * xyz.y + normal.z * xyz.z;
                // Se algum for maior que zero, parar de testar a normal
                if (prod > 0)
                {
                    inside = false;
                    break;
                }
                // testar próxima normal
            }
            // se todos os produtos vetoriais deste ponto forem menores que zero (o inside não muda), adicionar
            // o tile à lista de vptiles e parar de testar os pontos deste tile
            if (inside)
            {
                vptiles.push_back(tile);
                break;
            }
            // testar próximo ponto
        }
        // testar próximo tile
    }
    return vptiles;
}
