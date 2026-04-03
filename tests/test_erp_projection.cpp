#include "test_erp_projection.hpp"
#include "erp.hpp"
#include "test_framework.hpp"
#include "utils.hpp"
#include <cassert>
#include <string>

TestERP::TestERP(std::string &log) {
  auto callback = [this]() { test_Projection(); };

  TestRegistry tests(log);
  tests.add("Projection Test", callback);
  tests.runAll();
};

void TestERP::test_Projection() {
  ERP erp(Resolution(1920, 1080), Tiling(6, 4));

  std::vector<Tile> tile_list = erp.get_tile_list();
  TEST_ASSERT(erp.n_tiles == 21, "test_Projection: n_tiles should be 21");
  TEST_ASSERT(erp.resolution[0] == 1920,
              "test_Projection: resolution[0] should be 1920");
  TEST_ASSERT(erp.resolution[1] == 1080,
              "test_Projection: resolution[1] should be 1080");
  TEST_ASSERT(erp.tiling[0] == 6, "test_Projection: tiling[0] should be 6");
  TEST_ASSERT(erp.tiling[1] == 4, "test_Projection: tiling[1] should be 4");
  TEST_ASSERT(erp.tile_resolution[0] == 320,
              "test_Projection: tile_resolution[0] should "
              "be 320"); // 1920 / 6
  TEST_ASSERT(erp.tile_resolution[1] == 270,
              "test_Projection: tile_resolution[1] should "
              "be 270"); // 1080 / 4
}
