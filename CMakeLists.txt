cmake_minimum_required(VERSION 3.10)
project(MeuProjetoCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

include_directories(include)

find_package(OpenCV REQUIRED)

add_executable(GetTilesCPP
src/projection.cpp
src/erp.cpp
src/seen_tiles.cpp
src/mat_rot.cpp
src/main.cpp
src/utils.cpp
src/csv_handler.cpp
)

target_link_libraries(GetTilesCPP ${OpenCV_LIBS})



