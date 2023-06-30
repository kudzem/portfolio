cmake_minimum_required(VERSION 3.10])
project(testris)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_executable(testris "testris.cpp" "game.cpp" "tetris.h" "game.h" "main.cpp" "field.h")