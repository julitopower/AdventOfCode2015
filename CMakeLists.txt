cmake_minimum_required(VERSION 2.8)
project("AdventOfCode")

find_package(Boost 1.40 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "--std=c++11")

add_subdirectory("1")
add_subdirectory("2")
add_subdirectory("3")
add_subdirectory("4")
