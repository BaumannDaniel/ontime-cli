cmake_minimum_required(VERSION 3.28)
project(tone_cli CXX)

set(CMAKE_CXX_STANDARD 20)
find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
find_package(ftxui REQUIRED)
find_package(Boost REQUIRED COMPONENTS uuid)
find_package(Boost REQUIRED COMPONENTS algorithm)
find_package(rxcpp CONFIG REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src)
enable_testing()
add_subdirectory(test/unit)