#include "erp.h"
#include "seen_tiles.h"
#include "types.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Configurações globais para os testes
Resolution resolution(1920, 1080);
Tiling tiling(6, 4);
Fov fov = Fov(deg2rad(110.0), deg2rad(90.0));
ViewportCoord viewport_coord(0.0, 1.0, 0.0);

// Declarações dos testes
class Test {
  public:
    ERP* proj;

    Test() = default;

    void test_Projection();
    void test_SeenTiles();
    void test_predictor();
    void test_CsvHandler();
};

int main() {
    Test test;
    test.test_Projection();
    test.test_SeenTiles();

    return 0;
}

void Test::test_Projection() {
    proj = new ERP(::resolution, ::tiling);

    cout << endl << "=======================================" << endl;
    cout << "testing projection" << endl;
    cout << "\t" << "tiling = " << proj->tiling.h << "x" << proj->tiling.w
         << endl;
    cout << "\t" << "resolution = " << proj->resolution.h << "x"
         << proj->resolution.w << endl;
    cout << "\t" << "tile resolution = " << proj->tile_resolution.w << "x"
         << proj->tile_resolution.h << endl;
    cout << "\t" << "no. of tiles = " << proj->n_tiles << endl;
    for (const Tile& tile : proj->tile_list) {
        cout << "\t\t" << "Tile index: " << tile.index
             << ", position: (m=" << tile.position.m
             << ", n=" << tile.position.n
             << "), borders len = " << tile.borders.size() << endl;
    }
}

void Test::test_SeenTiles() {
    cout << endl << "=======================================" << endl;
    cout << "testing SeenTiles" << endl;
    SeenTiles seen_tiles(fov, this->proj);
    std::vector<Tile> vptiles = seen_tiles.get_vptiles(viewport_coord);

    // informações sobre os tiles. fazer um loop também.
    cout << "\t" << "fov = " << fov.fov_x << "x" << fov.fov_y << endl;
    cout << "\t" << "viewport_coord = yaw " << viewport_coord.yaw << ", pitch "
         << viewport_coord.pitch << ", roll " << viewport_coord.roll << endl;
    cout << "\t" << "Number of visible tiles: " << vptiles.size() << endl;
    cout << "\t" << "Visible tiles indices: ";
    for (const Tile& tile : vptiles) {
        cout << tile.index << " ";
    };
    cout << endl;
}

void Test::test_predictor() {
    //     std::vector<Point3D> data(30);
    //     // preencher data com suas 30 amostras... carregar um arquivo,
    //     pode ser um csv.
    //      for (int i = 0; i < 30; ++i) {
    //         data[i] = Point3D(i, i*2, i*3); // exemplo de dados
    //     }

    //     auto future = predict_future(data, 10); // prever os próximos 10
    //     pontos

    //     for (const auto& p : future) {
    //         std::cout << p.x << ", " << p.y << ", " << p.z << "\n";
    //     }
}
void Test::test_CsvHandler() {}