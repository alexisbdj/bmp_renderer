cmake_minimum_required(VERSION 3.13.0)

add_executable(out)

include_directories(out include)

target_sources(out PRIVATE
    main.cpp
)

target_link_libraries(out bmprenderer)