#cmake_minimum_required(VERSION 3.5)
project(demo)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(server server_udp_local.cpp signal.cpp)
add_executable(client client_udp_local.cpp)
