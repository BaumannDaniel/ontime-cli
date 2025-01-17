cmake_minimum_required(VERSION 3.28)
project(ontime_cli CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM "x64")
#set(cli_DIR ${CMAKE_SOURCE_DIR}/vcpkg/packages/cli_x64-linux/share/cli)
find_package(cli REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(test/unit)