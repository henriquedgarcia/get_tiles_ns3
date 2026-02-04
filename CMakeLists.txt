cmake_minimum_required(VERSION 3.10)
project(MeuProjetoCPP)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(GetTilesCPP
src/projection.cpp
src/erp.cpp
src/seen_tiles.cpp
src/mat_rot.cpp
src/main.cpp
)