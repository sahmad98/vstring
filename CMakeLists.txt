cmake_minimum_required(VERSION 3.5)

project(VString C CXX)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -march=skylake-avx512")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -fopt-info-vec-all=vec.rpt")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

add_executable(vstring_test src/vstring_test.cpp)
add_executable(vstring_bench src/vstring_bench.cpp)

target_link_libraries(vstring_test LINK_PUBLIC gtest)
target_link_libraries(vstring_bench LINK_PUBLIC benchmark)
