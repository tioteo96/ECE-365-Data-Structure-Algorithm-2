cmake_minimum_required(VERSION 3.15)
project(spellcheck)

set(CMAKE_CXX_STANDARD 14)

add_executable(spellcheck main.cpp hash.h hash.cpp)