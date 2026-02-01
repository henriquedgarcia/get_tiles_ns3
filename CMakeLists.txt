cmake_minimum_required(VERSION 3.10)
project(MeuProjetoCPP)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(GetTilesCPP
    src/main.cpp
    src/seen_tiles.cpp
    src/projection.cpp
)