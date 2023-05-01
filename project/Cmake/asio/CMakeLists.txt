cmake_minimum_required(VERSION 3.5)
project(vcpkg VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/asio/include")
add_executable(main src/main.cpp)
target_link_libraries(main ws2_32 wsock32)
