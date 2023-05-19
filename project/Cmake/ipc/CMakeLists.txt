#cmake_minimum_required(VERSION 3.5)
project(demo)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -g")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#add_executable(main src/main.cpp src/UnnamedPipe.cpp src/Pipe.cpp src/MessageQueue.cpp src/ShareMemory.cpp src/Signal.cpp)

#add_executable(server src/ShareMemory.cpp)
add_executable(main src/main.cpp src/ShareMemory.cpp)
