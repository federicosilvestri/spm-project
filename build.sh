#!/usr/bin/env bash
#
# Simple script to build the program.
#
set -e

# delete the build root and recreate it
rm -rf build && mkdir build

# go to build dir
cd build

# use cMake tool to create the main makefile
cmake .. -DFF_DISABLE=OFF -DCMAKE_BUILD_TYPE=Release

# start the compilation
make VERBOSE=1

# leave building directory
echo "Leaving building directory and copying the binary file to benchmark_workspace.."
cd ..
cp build/spm_project benchmark_workspace/
echo "DONE!"
