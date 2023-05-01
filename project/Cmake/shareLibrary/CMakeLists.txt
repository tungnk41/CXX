cmake_minimum_required(VERSION 3.5)
project(shareLib VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


add_library(shareLib SHARED src/share.cpp)
add_executable(main src/main.cpp)
target_link_libraries(main shareLib)