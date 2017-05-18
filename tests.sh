#!/bin/bash
cmake .
cd src
g++ -Idir main.cpp -o ns
./ns
