#include "test_erp_transformations.hpp"
#include "coord_map.hpp"
#include "test_framework.hpp"
#include "utils.hpp"
#include <string>

TestErpTransformations::TestErpTransformations() {
  std::string title = "TestErpTransformations";
  TestRegistry tests(title + ":\n");

  tests.add("test_mn2uv", [this]() { test_mn2uv(); });
  tests.add("test_uv2mn", [this]() { test_uv2mn(); });
  tests.add("test_uv2ae", [this]() { test_uv2ae(); });
  tests.add("test_ae2uv", [this]() { test_ae2uv(); });
  tests.add("test_ae2xyz", [this]() { test_ae2xyz(); });
  tests.add("test_xyz2ae", [this]() { test_xyz2ae(); });
  tests.runAll();
};

void TestErpTransformations::test_mn2uv() {
  Resolution resolution(4320, 2160);
  PointMN mn(1360, 1825);
  PointUV uv = erp_space::mn2uv(mn, resolution);
  TEST_ASSERT(uv[0] == 0.31493055555555555 && uv[1] == 0.84513888888888888,
              "mn2uv transformation failed");
}

void TestErpTransformations::test_uv2mn() {
  Resolution resolution(4320, 2160);
  PointUV uv(0.315, 0.845);
  PointMN mn = erp_space::uv2mn(uv, resolution);
  TEST_ASSERT(mn[0] == 1360 && mn[1] == 1825, "uv2mn transformation failed");
}

void TestErpTransformations::test_uv2ae() {
  PointUV uv(0.315, 0.845);
  AePoint ae = erp_space::uv2ae(uv);
  TEST_ASSERT(ae[0] == -1.1623892818282235 && ae[1] == -1.0838494654884787,
              "uv2ae transformation failed");
}

void TestErpTransformations::test_ae2uv() {
  AePoint ae(-1.16, -1.08);
  PointUV uv = erp_space::ae2uv(ae);
  // Olha só o problema de arredondamento. Queria ter uma função de
  // arredondamento que arredondasse para um número específico de casas
  // decimais. Se fosse 3 casas decimais seria perfeito.
  TEST_ASSERT(uv[0] == 0.31538026601340141 && uv[1] == 0.84377467707849396,
              "ae2uv transformation failed");
}

void TestErpTransformations::test_ae2xyz() {
  AePoint ae = AePoint(-1.16, -1.08);
  Point3D xyz = ae2xyz(ae);
  TEST_ASSERT(xyz[0] == 0.18822004714496987 && xyz[1] == -0.88195780688494751 &&
                  xyz[2] == 0.43211530952679628,
              "ae2xyz transformation failed");
}

void TestErpTransformations::test_xyz2ae() {
  Point3D xyz = Point3D(0.188, -0.883, 0.432);
  AePoint ae = xyz2ae(xyz);
  TEST_ASSERT(ae[0] == -1.1603304622311306 && ae[1] == -1.0806613827154099,
              "xyz2ae transformation failed");
}
