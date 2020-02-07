cmake_minimum_required(VERSION 3.15)
project(dijkstra)

set(CMAKE_CXX_STANDARD 14)

add_executable(dijkstra main.cpp heap.cpp heap.h graph.cpp graph.h hash.cpp hash.h)