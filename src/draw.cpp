#include "draw.hpp"
#include "projection.hpp"

cv::Mat Draw::draw_tile_border(Projection* projection,
                               int tile_id,
                               int lum) {
  int h = projection->resolution[1];
  int w = projection->resolution[0];

  cv::Mat canvas(h, w, CV_8UC3);
  std::vector<PointMN> borders = projection->get_tile_list()[tile_id].borders;

  for (auto& border : borders) {
    int x = border[0];
    int y = border[1];

    canvas.at<cv::Vec3b>(y, x) = cv::Vec3b(lum, lum, lum);
  }

  return canvas;
};

cv::Mat Draw::draw_all_tiles_borders(Projection* projection,
                                     int lum) {
  int h = projection->resolution[1];
  int w = projection->resolution[0];
  cv::Mat canvas(h, w, CV_8UC3);

  for (const Tile& tile : projection->get_tile_list()) {
    for (const PointMN& border : tile.borders) {
      int x = border[0];
      int y = border[1];

      canvas.at<cv::Vec3b>(y, x) = cv::Vec3b(lum, lum, lum);
    }
  }

  return canvas;
};

cv::Mat Draw::draw_vp_mask(Projection* projection,
                           int lum) {
  int h = projection->resolution[1];
  int w = projection->resolution[0];
  cv::Mat canvas(h, w, CV_8UC3);

  /*
    canvas = np.zeros(self.projection.shape, dtype='uint8')
    belong = self.is_viewport(self.projection.xyz)
    canvas[belong] = lum
  */
  return canvas;
};

cv::Mat Draw::draw_vp_border(Projection* projection,
                             int lum) {
  int h = projection->resolution[1];
  int w = projection->resolution[0];
  cv::Mat canvas(h, w, CV_8UC3);

  /*
    canvas = np.zeros(self.projection.shape, dtype='uint8')
    vp_borders_xyz = get_borders_value(array=self.xyz, thickness=thickness)
    nm = self.projection.xyz2nm(vp_borders_xyz).astype(int)
    canvas[nm[0, ...], nm[1, ...]] = lum
  */

  return canvas;
};

cv::Mat Draw::draw_tiles_seen(Projection* projection,
                              int lum) {
  int h = projection->resolution[1];
  int w = projection->resolution[0];
  cv::Mat canvas(h, w, CV_8UC3);

  /*
    canvas = np.zeros(self.projection.shape, dtype='uint8')
    for tile in self.get_vptiles():
    canvas[tile.borders[0], tile.borders[1]] = lum
  */

  return canvas;
};
