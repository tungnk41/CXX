# run : git submodule add https://github.com/Orphis/boost-cmake.git
# change download boost-version in repack.sh
cmake_minimum_required(VERSION 3.5)
project(boostExample VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set pont to local boost  library 
#set(FETCHCONTENT_SOURCE_DIR_BOOST C:/boost-src)
add_subdirectory(boost-cmake)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC Boost::math)