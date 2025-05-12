#!/bin/bash

# Set the LD_LIBRARY_PATH for the libraries
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/roobz/fun/symbol-tally/external/poppler/install/lib:/home/roobz/fun/symbol-tally/external/opencv/build/lib

# Compile and build
if cmake --build build; then
    echo "Build succeeded."
    ./build/run
else
    echo "Build failed."
fi

