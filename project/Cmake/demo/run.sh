#! /bin/bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build --target all
