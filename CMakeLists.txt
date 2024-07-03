cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

project(bmp_renderer)

add_library(bmprenderer)

target_compile_features(bmprenderer PUBLIC cxx_std_20)

target_include_directories(bmprenderer PUBLIC include)

add_subdirectory(src)

add_subdirectory(test)