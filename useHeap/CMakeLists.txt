cmake_minimum_required(VERSION 3.15)
project(useHeap)

set(CMAKE_CXX_STANDARD 14)

add_executable(useHeap main.cpp heap.cpp heap.h hash.cpp hash.h)