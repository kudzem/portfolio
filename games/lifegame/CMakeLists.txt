cmake_minimum_required(VERSION 3.10])
project(life_game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_executable(pg "life_game.cpp")