cmake_minimum_required(VERSION 3.10)
project(Parallel_processes)

set(CMAKE_CXX_STANDARD 20)

add_executable(parent parent.cpp)
add_executable(child child.cpp)