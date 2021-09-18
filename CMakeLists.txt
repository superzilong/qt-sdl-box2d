cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW)

project(qt-sdl LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


function(GroupSourcesByFolder target)
  set(SOURCE_GROUP_DELIMITER "/")
  set(last_dir "")
  set(files "")

  get_target_property(sources ${target} SOURCES)

  foreach(file ${sources})
    file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file})
    get_filename_component(dir "${relative_file}" PATH)
    if(NOT "${dir}" STREQUAL "${last_dir}")
      if(files)
        source_group("${last_dir}" FILES ${files})
      endif()
      set(files "")
    endif()
    set(files ${files} ${file})
    set(last_dir "${dir}")
  endforeach()

  if(files)
    source_group("${last_dir}" FILES ${files})
  endif()
endfunction()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
find_package(SDL2 REQUIRED)

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB_RECURSE ui "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Example.cpp
        Example.h
)


add_executable(qt-sdl ${sources} ${headers} ${ui})

# add_subdirectory(graphic)

GroupSourcesByFolder(qt-sdl)

target_link_libraries(qt-sdl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(qt-sdl PRIVATE SDL2::SDL2)
#set_property(TARGET qt-sdl PROPERTY WIN32_EXECUTABLE true)
