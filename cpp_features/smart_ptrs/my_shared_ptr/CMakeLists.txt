cmake_minimum_required(VERSION 3.10])
project(cpp_new_features_review)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_executable(pg "my_shared_ptr_demo.cpp" "my_shared_ptr.h")