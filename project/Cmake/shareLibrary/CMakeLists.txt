cmake_minimum_required(VERSION 3.5)
project(shareLib VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# Build cpp file to DLL
# add_library(shareLib SHARED src/share.cpp)
# set_target_properties(shareLib PROPERTIES OUTPUT_NAME "anotherNameShareLib")


# Add external DLL
add_library(shareLib SHARED IMPORTED)
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    #If not set IMPORTED_LOCATION, cmake wikk search dll file in library search path, This can work if the DLL is located in a standard location that the linker knows about
    #Or we can set the Directory which cmake will search dll in that
    # LINK_DIRECTORIES(/path/to/library)
    set_target_properties(shareLib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/libshareLib.dll")
    set_target_properties(shareLib PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/libshareLib.dll.a")
    # Cmake automatic set DLLIMPORT base on IMPORTED_IMPLIB, but should explicit set DLLIMPORT
    set_target_properties(shareLib PROPERTIES DLLIMPORT "shareLib.dll")
endif()
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(main src/main.cpp)
target_link_libraries(main shareLib)