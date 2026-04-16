# --- gcc, cmake, pkg-config, opencv, ffmpeg ---
# No Linux e WSL
# sudo apt update
# sudo apt install build-essential cmake pkg-config libopencv-dev ffmpeg

cmake_minimum_required(VERSION 3.5)
project(GetTiles)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_library(gettiles
    src/projection.cpp
    src/erp.cpp
    src/seen_tiles.cpp
    src/types.cpp
    src/utils.cpp
    src/draw.cpp
    src/viewport.cpp
    src/coord_map.cpp
)

target_include_directories(gettiles PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(gettiles PUBLIC ${OpenCV_LIBS})

add_executable(tests
    tests/main_tests.cpp
    tests/test_framework.cpp
    tests/test_erp_projection.cpp
    tests/test_erp_transformations.cpp
    tests/test_SeenTiles.cpp    
)
target_link_libraries(tests PRIVATE gettiles)
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
