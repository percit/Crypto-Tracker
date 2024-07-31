#!/bin/bash

docker run -it --rm \
--device /dev/dri/ \
-e DISPLAY=$DISPLAY \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v $PWD:/workspace \
-w /workspace/ \
--name qt-docker qt6:1.0.0