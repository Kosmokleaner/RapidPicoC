#!/bin/bash

# Get the full, absolute path to the script's directory
SCRIPT_DIR=$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)

echo "setup in: $SCRIPT_DIR"
cd $SCRIPT_DIR
# all auto generated files go in here for less mess
mkdir -p build
cd build
# cmake generated the makefile
cmake ..
# we run make from build folder to compile and link the add
make
# output is build/<name>.uf2
# copy to the Raspberry Pi Pico



