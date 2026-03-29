#include "test_erp_projection.hpp"
#include "erp.hpp"
#include "test_framework.hpp"
#include "utils.hpp"
#include <cassert>

TestERP::TestERP() {
  this->resolution = Resolution(1920, 1080);
  this->tiling = Tiling(6, 4);
  this->erp = new ERP(this->resolution, this->tiling);
  TestRegistry tests;
  tests.add("Projection Test", [this]() { test_Projection(); });
  tests.runAll();
};

void TestERP::test_Projection() {
  erp = new ERP(this->resolution, this->tiling);
  std::vector<Tile> tile_list = make_tile_list(erp);
  assert(erp->n_tiles == 8);
  assert(erp->tile_resolution[0] == 480);
  assert(erp->tile_resolution[1] == 540);
}
