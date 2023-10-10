cmake_minimum_required(VERSION 3.24)

project(SlidingPuzzle VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.6 REQUIRED COMPONENTS Core Quick QuickControls2)

add_subdirectory(src)
