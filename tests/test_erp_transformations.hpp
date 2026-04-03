#include "coord_map.hpp"
#include "test_framework.hpp"
#include <sstream>

class TestErpTransformations {
  void test_mn2uv();
  void test_uv2ae();
  void test_ae2xyz();
  void test_xyz2ae();
  void test_ae2uv();
  void test_uv2mn();

 public:
  TestErpTransformations();
};
