#! /bin/bash
#rm -rf build
#cmake -S . -B build -G "Unix Makefiles"
#cmake --build build --target all
#./build/main

rm -rf build
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
