cmake_minimum_required(VERSION 3.5)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(SDL2 REQUIRED CONFIG)
find_package(box2d REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FILE(GLOB_RECURSE ui "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

add_executable(qt-sdl-box2d ${sources} ${headers} ${ui})

list(APPEND allFiles ${sources} ${ui} ${headers})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${allFiles})

target_link_libraries(qt-sdl-box2d PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(qt-sdl-box2d PRIVATE SDL2::SDL2)
target_link_libraries(qt-sdl-box2d PRIVATE box2d::box2d)
target_link_libraries(qt-sdl-box2d PUBLIC SDL2_gfx::SDL2_gfx)
target_link_libraries(qt-sdl-box2d PUBLIC spdlog::spdlog_header_only)


