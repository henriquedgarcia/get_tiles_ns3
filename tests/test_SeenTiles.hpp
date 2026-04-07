#include "seen_tiles.hpp"
#include "test_framework.hpp"
#include <sstream>

class TestSeenTiles {
  void test_set_normals_default();
  void test_tile_is_in_frustrum();
  void test_is_in();
  void test_get_vptiles();

 public:
  TestSeenTiles();
};
