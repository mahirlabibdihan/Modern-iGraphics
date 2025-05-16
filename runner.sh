#!/bin/bash

# Exit immediately on error
set -e

# Use default source file if none is provided
SOURCE_FILE="${1:-iMain.cpp}"
echo "Using source file: $SOURCE_FILE"

# Make sure the output directories exist
mkdir -p bin obj

# Compile the source file to an object file
g++ -w -fexceptions -g -I. -IOpenGL/include -c "$SOURCE_FILE" -o obj/object.o

# Link the object file to create the executable
g++ -o bin/opengl obj/object.o -L./OpenGL/lib -lGL -lGLU -lglut -pthread

# g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 iMain.cpp -o bin/opengl.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut && ./bin/opengl.exe

echo "Finished building."

# Run the executable
./bin/opengl
