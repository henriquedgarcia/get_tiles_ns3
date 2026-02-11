#include <iostream>
#include "types.h"
#include "erp.h"
#include "seen_tiles.h"
#include "utils.h"

using namespace std;

int main()
{
     // Testes
     Resolution resolution(1920, 1080);
     Tiling tiling(6, 4);

     ERP proj(resolution, tiling);
     Fov fov = Fov(deg2rad(110.0), deg2rad(90.0));
     SeenTiles seen_tiles(fov, &proj);
     ViewportCoord viewport_coord(0.0, 1.0, 0.0);
     std::vector<Tile> vptiles = seen_tiles.get_vptiles(viewport_coord);
     
     // informações sobre os tiles. fazer um loop também.
     cout << "tiling = " << tiling.h << "x" << tiling.w << endl;
     cout << "resolution = " << resolution.h << "x" << resolution.w << endl;
     cout << "fov = " << fov.fov_x << "x" << fov.fov_y << endl;
     cout << "viewport_coord = yaw " << viewport_coord.yaw << ", pitch " << viewport_coord.pitch << ", roll " << viewport_coord.roll << endl;
     cout << "Visible tiles indices: ";for (const Tile &tile : vptiles){cout << tile.index << " ";};cout << endl;
     cout << "Number of visible tiles: " << vptiles.size();
     cout << endl;


//     std::vector<Point3D> data(30);
//     // preencher data com suas 30 amostras... carregar um arquivo, pode ser um csv.
//      for (int i = 0; i < 30; ++i) {
//         data[i] = Point3D(i, i*2, i*3); // exemplo de dados
//     }

//     auto future = predict_future(data, 10); // prever os próximos 10 pontos

//     for (const auto& p : future) {
//         std::cout << p.x << ", " << p.y << ", " << p.z << "\n";
//     }

     return 0;
}