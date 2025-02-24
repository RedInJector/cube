cmake_minimum_required(VERSION 3.0)

project(presentation)


set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR ${PROJECT_SOURCE_DIR}/3rdparty/SDL2/cmake)
find_package(SDL2 REQUIRED)

set(CUBE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)



add_subdirectory(src)

