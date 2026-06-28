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
  Fov fov(deg2rad(110.0), deg2rad(90.0));
  Resolution resolution(4320, 2160);
  Tiling tiling(6, 4);
  PointYawPitchRoll viewpoint(0, 0, 0);

  auto projection = std::make_unique<ERP>(resolution, tiling);

  Viewport viewport(resolution, fov, *projection);
  PointYawPitchRoll yaw_pitch_roll(0, 0, 0);
  cv::Mat proj_frame = cv::Mat::zeros(2160, 4320, CV_8UC3);
  // cv::Mat extracted_viewport =
  //     viewport.extract_viewport(proj_frame, yaw_pitch_roll);

  std::string image_path = "erp1.png";
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

  // Verificar se carregou corretamente
  if (img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return;
  }
  std::cout << "Exibindo: " << image_path << std::endl;

  cv::imshow("Display window", img);
  int k = cv::waitKey(0); // Wait for a keystroke in the window

  std::cout << "convertendo: " << image_path << std::endl;
  cv::imwrite("starry_night.png", img);

  // std::string path = "minha_imagem.jpg";

  // Carregar a imagem
  // cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

  // if (img.empty()) {
  //   std::cerr << "Erro: não foi possível abrir a imagem!" << std::endl;
  //   return void;
  // }

  // // Mostrar a imagem em uma janela
  // cv::imshow("Imagem", img);

  // Esperar tecla para fechar
  // cv::waitKey(0);
}
