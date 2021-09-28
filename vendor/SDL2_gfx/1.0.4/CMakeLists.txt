cmake_minimum_required(VERSION 3.5)

project (SDL2_gfx)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(SDL2 REQUIRED)

FILE(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(SDL2_gfx ${sources} ${headers})
add_library(SDL2_gfx::SDL2_gfx ALIAS SDL2_gfx)

target_link_libraries(SDL2_gfx PRIVATE SDL2::SDL2)

target_include_directories(SDL2_gfx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})