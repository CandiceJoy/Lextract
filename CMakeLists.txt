cmake_minimum_required(VERSION 3.24)
project(lextract)

set(CMAKE_CXX_STANDARD 20)

add_executable(lextract util.cpp wad.cpp main.cpp)
target_include_directories(lextract PUBLIC ./)
