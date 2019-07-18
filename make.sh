#!/bin/bash

#========================================================================================
# Just a quick script to make bin folder, then build and run.
#========================================================================================

# Make folder if it doesn't exist before.
mkdir -p bin;
cd bin;
cmake ../ && make -j4 && ./n-body;
