cmake_minimum_required(VERSION 3.28)
project(ontime_cli CXX)

set(CMAKE_CXX_STANDARD 20)
find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
find_package(cli REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(test/unit)