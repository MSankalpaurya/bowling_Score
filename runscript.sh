#!/bin/bash

# Exit immediately if a command fails
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run cmake to generate Makefiles
cmake ..

# Compile the project
cmake --build .

# Run the executable
./BowlingScore
