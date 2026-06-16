#include "test_SeenTiles.hpp"
#include "erp.hpp"
#include "seen_tiles.hpp"
#include "types.hpp"
#include "utils.hpp"

TestSeenTiles::TestSeenTiles() {
  TestRegistry tests("TestSeenTiles:\n");
  tests.add("test_set_normals_default",
            [this]() { test_set_normals_default(); });
  tests.add("test_get_vptiles", [this]() { test_get_vptiles(); });
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
  Resolution resolution(4320, 2160);
  Tiling tiling(6, 4);
  PointYawPitchRoll viewpoint(0, 0, 0);
  
  auto erp = std::make_unique<ERP>(resolution, tiling);
  SeenTiles seen_tiles(fov, *erp);
  
  std::vector<Tile> tiles_list = seen_tiles.get_vptiles(viewpoint);
  
  bool result = tiles_list.size() == 6 && tiles_list[0].index == 2 &&
                tiles_list[1].index == 3 && tiles_list[2].index == 8 &&
                tiles_list[3].index == 9 && tiles_list[4].index == 14 &&
                tiles_list[5].index == 15;
  TEST_ASSERT(result, "test_get_vptiles failed");
}
