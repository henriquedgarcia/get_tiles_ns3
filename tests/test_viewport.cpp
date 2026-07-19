#include "test_viewport.hpp"
#include "erp.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "viewport.hpp"

TestViewport::TestViewport() {
  auto test_fn = [this]() { test_extract_viewport(); };

  TestRegistry tests("TestViewport:\n");
  tests.add("test_extract_viewport", test_fn);
  tests.runAll();
}

void TestViewport::test_extract_viewport() {
  std::string image_path = "tests/assets/erp1.png";
  Fov fov(deg2rad(110.0), deg2rad(90.0));
  Resolution resolution(2160, 1080);
  Tiling tiling(6, 4);

  auto projection = std::make_unique<ERP>(resolution, tiling);

  Viewport viewport(resolution, fov, *projection);
  PointYawPitchRoll yaw_pitch_roll(0, 0, 0);
  cv::Mat proj_frame = cv::imread(image_path, cv::IMREAD_COLOR);

  TEST_ASSERT(!proj_frame.empty(), "Could not read image: " + image_path);

  cv::Mat extracted_viewport =
      viewport.extract_viewport(proj_frame, yaw_pitch_roll);

  std::cout << "Exibindo: " << image_path << std::endl;
  cv::imshow("Display window", extracted_viewport);
  cv::waitKey(0); // Wait for a keystroke in the window

  std::cout << "salvando: " << image_path << std::endl;
  cv::imwrite("tests/assets/extracted_viewport.png", extracted_viewport);
  std::cout << "saindo: " << std::endl;
}
