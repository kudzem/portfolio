cmake_minimum_required(VERSION 3.10])
SET(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
project(testris)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testris "testris.cpp" "game.cpp" "tetris.h" "game.h" "main.cpp" "board.h" "field.h" "figure.h")
target_link_libraries(testris -pthread)
