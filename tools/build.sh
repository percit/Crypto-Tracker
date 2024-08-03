#!/bin/bash

mkdir build
cd build
cmake .. -DBUILD_TESTS=ON
ninja -j16