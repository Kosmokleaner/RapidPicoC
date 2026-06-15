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

# copy the following lines for more convenient single letter iteration
# or run the build script once with "source ./build"
alias b="./build.sh"
alias u="picotool load -x build/picow_blink.elf"
alias p="putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N"



