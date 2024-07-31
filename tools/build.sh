#!/bin/bash

cd build
cmake .. -DBUILD_TESTS=ON
ninja -j16