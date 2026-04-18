#include "seen_tiles.hpp"
#include <array>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "projection.hpp"
#include "types.hpp"
#include "utils.hpp"

SeenTiles::SeenTiles(const Fov &fov, const Projection *projection) {
  this->fov = fov;
  this->projection = projection;
  this->tiling = projection->tiling;
  this->resolution = projection->resolution;

  this->set_normals_default();
}

void SeenTiles::rotate_frustrum() {
  cv::Quatd quat = create_quaternion(this->yaw_pitch_roll);
  default_frustrum = create_default_frustrum(this->fov);
  for (int i = 0; i < 4; i++) {
    Normal normal = this->default_frustrum.normals[i];
    this->rotated_frustrum.normals[i] = rotate(normal, quat);
  }
}

void SeenTiles::set_normals_default() {
  this->default_frustrum = create_default_frustrum(this->fov);
}

std::vector<Tile> SeenTiles::get_vptiles(PointYawPitchRoll yaw_pitch_roll) {
  this->yaw_pitch_roll = yaw_pitch_roll;
  std::vector<Tile> vptiles;

  // Se o tiling é 1x1 retorne logo o único tile.
  if (this->tiling == Tiling(1, 1)) {
    vptiles.push_back(this->projection->tile_list[0]);
    return vptiles;
  }

  this->rotate_frustrum();

  for (const Tile &tile : this->projection->tile_list) {
    if (this->tile_is_in_frustrum(tile)) {
      vptiles.push_back(tile);
    }
  }
  return vptiles;
}

bool SeenTiles::tile_is_in_frustrum(Tile tile) {
  /* Um tile está no frustrum se pelo menos um ponto estiver dentro do
   * frustrum */
  for (const PointMN &point : tile.borders) {
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
  for (const Normal &normal : this->rotated_frustrum.normals) {
    double prod = dot(normal, xyz);
    if (prod > 0) {
      return false;
    }
  }
  return true;
}
