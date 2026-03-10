#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cmath>
#include <numbers> // pi
#include <numeric> // std::iota
#include <vector>

#include "types.hpp" // Point3D
#include "projection.hpp" // Projection

class Imagem;

class GnomonicProjection : public Projection {
  public:
    Point3D mn2xyz(const ImagePoint &mn) const override;
    // ImagePoint xyz2mn(const Point3D &xyz) const override;
};

class Viewport {
  public:
    Viewport(const Resolution& resolution, const Tiling& tiling);
    // std::vector<Tile> tile_list;
    // Resolution resolution;
    // Resolution tile_resolution;
    // Tiling tiling;
    // int n_tiles;

    // extract_viewport(self, proj_frame, yaw_pitch_roll=None) -> np.ndarray:
    Imagem extract_viewport();
    std::vector<ImagePoint> get_tile_borders(const Tile& tile);

    virtual Point3D mn2xyz(const ImagePoint& mn) const = 0;
};

#endif // VIEWPORT_H
