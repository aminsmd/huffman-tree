cmake_minimum_required(VERSION 3.6)
project(huffman_tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp header.h)
add_executable(huffman_tree ${SOURCE_FILES})