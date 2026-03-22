#include <iostream>
#include "test.hpp"

int main() {
  Test test;
  std::cout << "Running tests..." << std::endl;
  std::cout << std::endl << "== testing Projection " << std::endl;
  test.test_Projection();
  // std::cout << "== testing SeenTiles " << std::endl;
  // test.test_SeenTiles();
  // std::cout << std::endl << "== testing predictor " << std::endl;
  // test.test_predictor();

  // std::cout << std::endl << "== testing OpenCV " << std::endl;
  // test.test_OpenCV();
  return 0;
}

// Declarações dos testes
