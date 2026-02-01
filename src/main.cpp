#include <iostream>
#include "types.h"

int main() {
    // Testes
    Tiling tiling(6, 4);
    Resolution resolution(1920, 1080);

    std::cout << "tiling.h: " << tiling.h
              << ", tiling.w: " << tiling.w
              << std::endl;

    std::cout << "resolution.h: " << resolution.h
              << ", resolution.w: " << resolution.w
              << std::endl;

    return 0;
}