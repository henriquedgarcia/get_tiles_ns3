#include "test.hpp"
#include "erp.hpp"
#include "erp_map.hpp"
#include "seen_tiles.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <filesystem>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;

class TestErpTransform : public Test {
public:
  void run() {
    test_mn2uv();
    test_xyz2ae();
    test_ae2xyz();
    test_ae2uv();
    test_uv2ae();
    test_uv2mn();
  }

  Point3D xyz;
  AePoint ae;

  void test_xyz2ae() {
    xyz = Point3D(1.0, 2.0, 3.0);
    ae = erp::xyz2ae(xyz);
    cout << "xyz: (" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << ") -> "
         << "ae: (" << ae[0] << ", " << ae[1] << ")" << endl;
  }

  void test_ae2xyz() {
    ae = AePoint(deg2rad(30.0), deg2rad(45.0));
    xyz = erp::ae2xyz(ae);
    cout << "ae: (" << ae[0] << ", " << ae[1] << ") -> "
         << "xyz: (" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << ")"
         << endl;
  }

  void test_ae2uv() {
    AePoint ae(deg2rad(30.0), deg2rad(45.0));
    PointUV uv = erp::ae2uv(ae);
    cout << "ae: (" << ae[0] << ", " << ae[1] << ") -> "
         << "uv: (" << uv[0] << ", " << uv[1] << ")" << endl;
  }

  void test_uv2ae() {
    PointUV uv(0.5, 0.5);
    AePoint ae = erp::uv2ae(uv);
    cout << "uv: (" << uv[0] << ", " << uv[1] << ") -> "
         << "ae: (" << ae[0] << ", " << ae[1] << ")" << endl;
  }

  void test_uv2mn() {
    PointUV uv(0.5, 0.5);
    PointMN mn = erp::uv2mn(uv, resolution);
    cout << "uv: (" << uv[0] << ", " << uv[1] << ") -> "
         << "mn: (" << mn[0] << ", " << mn[1] << ")" << endl;
  }

  void test_mn2uv() {
    PointMN mn(960, 540);
    PointUV uv = erp::mn2uv(mn, resolution);
    cout << "mn: (" << mn[0] << ", " << mn[1] << ") -> "
         << "uv: (" << uv[0] << ", " << uv[1] << ")" << endl;
  }
};

class TestERP : public Test {
public:
  void run() { test_Projection(); }
};

Test::Test()
    : resolution(1920, 1080), tiling(6, 4), fov(deg2rad(110.0), deg2rad(90.0)),
      yaw_pitch_roll(0.0, 1.0, 0.0) {};

void Test::test_Projection() {
  proj = new ERP(this->resolution, this->tiling);
  proj->make_tile_list();

  cout << endl << "=======================================" << endl;
  cout << "testing projection" << endl;
  cout << "\t"
       << "tiling = " << proj->tiling[1] << "x" << proj->tiling[0] << endl;
  cout << "\t"
       << "resolution = " << proj->resolution[1] << "x" << proj->resolution[0]
       << endl;
  cout << "\t"
       << "tile resolution = " << proj->tile_resolution[0] << "x"
       << proj->tile_resolution[1] << endl;
  cout << "\t" << "no. of tiles = " << proj->n_tiles << endl;

  for (const Tile &tile : proj->tile_list) {
    cout << "\t\t"
         << "Tile index: " << tile.index
         << ", position: (m=" << tile.position[0] << ", n=" << tile.position[1]
         << "), borders len = " << tile.borders.size() << endl;
  }
};

void Test::test_SeenTiles() {
  SeenTiles seen_tiles(fov, this->proj);
  std::vector<Tile> vptiles = seen_tiles.get_vptiles(yaw_pitch_roll);

  // informações sobre os tiles. fazer um loop também.
  cout << "\t" << "fov = " << fov[0] << "x" << fov[1] << endl;
  cout << "\t"
       << "yaw_pitch_roll = (yaw=" << yaw_pitch_roll[0]
       << ", pitch=" << yaw_pitch_roll[1] << ", roll=" << yaw_pitch_roll[2]
       << ")" << endl;
  cout << "\t" << "Number of visible tiles: " << vptiles.size() << endl;
  cout << "\t" << "Visible tiles indices: ";
  for (const Tile &tile : vptiles) {
    cout << tile.index << " ";
  };
  cout << endl;
};

void Test::test_predictor() {
  std::vector<Point3D> data(30);
  // preencher data com suas 30 amostras... carregar um arquivo, pode ser um
  // csv.
  for (int i = 0; i < 30; ++i) {
    data[i] = Point3D(i, i * 2, i * 3); // exemplo de dados
  }

  auto future = predict_future(data, 10); // prever os próximos 10 pontos

  for (const auto &p : future) {
    // std::cout << p.x << ", " << p.y << ", " << p.z << "\n";
  }
};

void Test::test_CsvHandler() {};

void Test::test_OpenCV() {
  std::string image_path = "teste.png";
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

  if (img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return;
  }
  std::cout << "Exibindo: " << image_path << std::endl;

  cv::imshow("Display window", img);
  int k = cv::waitKey(0); // Wait for a keystroke in the window

  std::cout << "convertendo: " << image_path << std::endl;
  cv::imwrite("starry_night.png", img);
};
