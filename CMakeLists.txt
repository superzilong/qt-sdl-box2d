cmake_minimum_required(VERSION 3.5)

project(qt-sdl-box2d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2_gfx/1.0.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
