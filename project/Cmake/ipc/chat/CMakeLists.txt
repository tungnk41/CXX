cmake_minimum_required(VERSION 3.4)
project(chat)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -std=c++11 -pthread")

add_executable(server server.cpp)
add_executable(client client.cpp)
target_link_libraries(server pthread)
target_link_libraries(client pthread)