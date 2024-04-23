cmake_minimum_required(VERSION 3.27)
project(smoothlife C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(raylib URL "https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz")
FetchContent_MakeAvailable(raylib)

add_executable(smoothlife src/main.c
        src/lib/grid.c
        src/include/grid.h
        src/include/args.h
        src/lib/args.c
)
target_link_libraries(smoothlife raylib)
