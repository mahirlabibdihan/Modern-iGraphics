#!/bin/bash

# Exit immediately on error
set -e

# Use default source file if none is provided
SOURCE_FILE="${1:-iMain.cpp}"
echo "Using source file: $SOURCE_FILE"

# Make sure the output directories exist
mkdir -p bin obj

# Compile the source file to an object file
g++ -Wall -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/irrKlang -c "$SOURCE_FILE" -o obj/object.o

# Link the object file to create the executable
g++ -o bin/opengl obj/object.o -L./OpenGL/lib ./OpenGL/lib/libIrrKlang.so -lGL -lGLU -lglut -pthread

echo "Finished building."

# Run the executable
./bin/opengl
