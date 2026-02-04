#include <iostream>
#include "types.h"
#include "erp.h"
#include "seen_tiles.h"

using namespace std;

int main()
{
     // Testes
     Resolution resolution(1920, 1080);
     Tiling tiling(6, 4);

     cout << "tiling.h: " << tiling.h
          << ", tiling.w: " << tiling.w
          << endl;

     cout << "resolution.h: " << resolution.h
          << ", resolution.w: " << resolution.w
          << endl;

     ERP proj(resolution, tiling);
     double fov_x = PI * 110.0 / 180.0;
     double fov_y = PI * 90.0 / 180.0;
     SeenTiles seen_tiles(Fov(fov_x, fov_y), &proj);
     std::vector<Tile> vptiles = seen_tiles.get_vptiles(ViewportCoord(0.0, 0.0, 0.0));
     
     // informações sobre os tiles. fazer um loop também.
     cout << "Visible tiles indices: ";
     for (const Tile &tile : vptiles)
     {
         cout << tile.index << " ";
     }
     cout << endl << "Number of visible tiles: " << vptiles.size() << endl;
     
     return 0;
}