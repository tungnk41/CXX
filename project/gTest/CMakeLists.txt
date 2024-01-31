cmake_minimum_required(VERSION 3.22.1)
project(gTest VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

################################
# GTest as Sub Module
################################
#ADD_SUBDIRECTORY (googletest-1.14.0)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#add_executable(main src/main.cpp )
#target_link_libraries(main  gtest gmock gtest_main)
################################

add_compile_options(-fpermissive)
include_directories(include)
link_directories(lib)
add_executable(MainTest src/test/MainTest.cpp)
target_link_libraries(MainTest gtest gmock gtest_main)
