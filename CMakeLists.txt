cmake_minimum_required(VERSION 3.10.0)

project(zlog)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Werror)

include_directories(./include)

add_executable(zlog main.cpp)
target_link_libraries(zlog pthread)