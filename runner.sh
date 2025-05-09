#!/bin/bash

# Exit immediately on error
set -e

# Check for source file argument
if [ -z "$1" ]; then
    echo "Usage: $0 source_file"
    exit 1
fi

# Set the base directory for g++ (optional if g++ is in your PATH)
# BASE_DIR=/usr/bin
# export PATH="$BASE_DIR:$PATH"

# Make sure the output directory exists
mkdir -p exec

# Compile the source file to an object file
g++ -Wall -fexceptions -g -IOpenGL/include -IOpenGL/include/irrKlang -c "$1" -o exec/object.o

# Link the object file to create the executable
g++ -o exec/opengl exec/object.o -L./OpenGL/lib ./OpenGL/lib/libIrrKlang.so -lGL -lGLU -lglut -pthread


echo "Finished building."

# Run the executable
./exec/opengl
