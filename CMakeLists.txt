# --- gcc, cmake, pkg-config, opencv, ffmpeg ---
# No Linux e WSL
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
    src/types.cpp
    src/utils.cpp
    src/draw.cpp
    src/viewport.cpp
    src/test.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(main PRIVATE ${OpenCV_LIBS})
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
