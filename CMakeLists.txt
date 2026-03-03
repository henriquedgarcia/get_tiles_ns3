cmake_minimum_required(VERSION 3.10)
project(MeuProjetoCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/opencv/include")
set(OpenCV_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/opencv/lib")
set(OpenCV_DLL_DIR "${CMAKE_SOURCE_DIR}/thirdparty/opencv/dll")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIR})
link_directories(${OpenCV_LIB_DIR})

add_executable(GetTilesCPP
    src/projection.cpp
    src/erp.cpp
    src/seen_tiles.cpp
    src/mat_rot.cpp
    src/main.cpp
    src/utils.cpp
    src/csv_handler.cpp
)

target_link_libraries(GetTilesCPP opencv_world4130)

set_target_properties(GetTilesCPP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

install(TARGETS GetTilesCPP 
        DESTINATION bin)

install(FILES
        ${OpenCV_DLL_DIR}/opencv_world4130.dll
        ${OpenCV_DLL_DIR}/opencv_videoio_ffmpeg4130_64.dll
        DESTINATION bin
)

add_custom_command(TARGET GetTilesCPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${OpenCV_DLL_DIR}/opencv_world4130.dll"
            $<TARGET_FILE_DIR:GetTilesCPP>
    COMMAND ${CMAKE_COMMAND} -E copy
            "${OpenCV_DLL_DIR}/opencv_videoio_ffmpeg4130_64.dll"
            $<TARGET_FILE_DIR:GetTilesCPP>
)
