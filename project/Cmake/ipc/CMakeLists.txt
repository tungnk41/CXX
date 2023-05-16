#cmake_minimum_required(VERSION 3.5)
project(demo)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(main src/main.cpp src/upipe.cpp src/pipe.cpp)
