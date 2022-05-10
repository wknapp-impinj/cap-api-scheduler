cmake_minimum_required(VERSION 3.9)

project(scheduler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -pthread")

add_subdirectory(src)