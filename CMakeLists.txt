# --- gcc, cmake, pkg-config, opencv, ffmpeg ---

# No MSYS2 (UCRT64)
# pacman -Syu
# pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-pkg-config mingw-w64-ucrt-x86_64-opencv mingw-w64-ucrt-x86_64-ffmpeg 

# No Linux
# sudo apt update
# sudo apt install build-essential cmake pkg-config libopencv-dev ffmpeg

cmake_minimum_required(VERSION 3.5)
project(GetTiles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(SOURCES
    src/main.cpp
    src/projection.cpp
    src/erp.cpp
    src/seen_tiles.cpp
    src/mat_rot.cpp
    src/utils.cpp
    src/csv_handler.cpp
)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE ${OpenCV_LIBS})
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
