#ifndef TESTS_HPP
#define TESTS_HPP

#include <filesystem>
#include <iostream>

#include "projection.hpp"
#include "types.hpp"

class Test {
 public:
  Projection* proj;
  Resolution resolution;
  Tiling tiling;
  Fov fov;
  ViewportCoord viewport_coord;

  Test();

  void test_Projection();

  void test_SeenTiles();

  void test_predictor();

  void test_CsvHandler();

  void test_OpenCV();
};
#endif  // TESTS_HPP