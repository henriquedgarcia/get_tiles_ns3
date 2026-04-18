#include "test_SeenTiles.hpp"
#include "erp.hpp"
#include "seen_tiles.hpp"
#include "types.hpp"
#include "utils.hpp"

TestSeenTiles::TestSeenTiles() {
  TestRegistry tests("TestSeenTiles:\n");
  tests.add("test_set_normals_default", [this]() { test_set_normals_default(); });
  tests.add("test_get_vptiles", [this]() { test_get_vptiles(); });
  // tests.add("test_is_in", [this]() { test_is_in(); });
  // tests.add("test_is_in_frustrum", [this]() { test_is_in_frustrum(); });
  tests.runAll();
}

void TestSeenTiles::test_set_normals_default() {
  Fov fov(deg2rad(110.0), deg2rad(90.0));
  Frustrum frustrum = create_default_frustrum(fov);

  Normal normal_left(-0.8191520442889918, 0.0, -0.57357643635104616);
  Normal normal_right(-0.8191520442889918, 0.0, 0.57357643635104616);
  Normal normal_top(-0.70710678118654746, 0.70710678118654757, 0);
  Normal normal_bottom(-0.70710678118654746, -0.70710678118654757, 0);

  bool result = true;
  result &= frustrum.normals[0] == normal_left;
  result &= frustrum.normals[1] == normal_right;
  result &= frustrum.normals[2] == normal_top;
  result &= frustrum.normals[3] == normal_bottom;
  TEST_ASSERT(result, "test_set_normals_default failed");
}

void TestSeenTiles::test_get_vptiles() {
  Fov fov(deg2rad(110.0), deg2rad(90.0));
  ERP *erp = new ERP(Tiling(6, 4), Resolution(4320, 2160));
  
  SeenTiles seen_tiles(fov, erp);
  std::vector<Tile> tiles_list =
      seen_tiles.get_vptiles(PointYawPitchRoll(0, 0, 0));
  bool result = tiles_list.size() == 3 && tiles_list[0].index == 6 &&
                tiles_list[1].index == 7 && tiles_list[2].index == 8;
  TEST_ASSERT(result, "test_get_vptiles failed");
}
