#include "projection.hpp"
#include "types.hpp"
#include <vector>

using namespace std;

Projection::Projection(const Resolution &resolution, const Tiling &tiling)
    : resolution(resolution), tiling(tiling)
{
    this->n_tiles = tiling.w * tiling.h;
    this->tile_resolution.w = resolution.w / tiling.w;
    this->tile_resolution.h = resolution.h / tiling.h;
    this->tile_list = this->make_tile_list();
}

vector<Tile> Projection::make_tile_list()
{
    int index = 0;
    vector<Tile> vptiles;

    for (int h = 0; h < this->tiling.h; h++)
    {
        for (int w = 0; w < this->tiling.w; w++)
        {
            ImagePoint position(w * (this->tile_resolution.w),
                                h * (this->tile_resolution.h));
            Tile tile(index, this->tile_resolution, position);
            tile.borders = this->get_tile_borders(tile);
            vptiles.push_back(tile);
            index++;
        }
    }
    return vptiles;
}

vector<ImagePoint> Projection::get_tile_borders(const Tile &tile)
{
    vector<ImagePoint> borders;

    int left_x = tile.position.m;
    int right_x = tile.position.m + tile.resolution.w;

    int top_y = tile.position.n;
    int bottom_y = tile.position.n + tile.resolution.h;

    for (int x = left_x; x < right_x; x++)
    {
        borders.push_back(ImagePoint(x, top_y));    // Top edge
        borders.push_back(ImagePoint(x, bottom_y)); // Bottom edge
    }
    for (int y = top_y; y < bottom_y; y++)
    {
        borders.push_back(ImagePoint(left_x, y));  // Left edge
        borders.push_back(ImagePoint(right_x, y)); // Right edge
    }

    return borders;
};
