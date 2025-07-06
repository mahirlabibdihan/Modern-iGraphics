#!/bin/bash

# Exit immediately on error
set -e

# sudo apt install libsdl2-dev libsdl2-mixer-dev

# Use default source file if none is provided
SOURCE_FILE="${1:-iMain.cpp}"
echo "Using source file: $SOURCE_FILE"

# Make sure the output directories exist
mkdir -p bin obj

if [[ "$OSTYPE" == "linux-gnu"* ]]
then
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 -IOpenGL/include/Freetype -c "$SOURCE_FILE" -o obj/object.o
    g++ -o bin/opengl obj/object.o -lGL -lGLU -lglut -pthread -lSDL2 -lSDL2main -lSDL2_mixer -lfreetype
    echo "Finished building."
else
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 "$SOURCE_FILE" -o bin/opengl.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut -lfreetype
    echo "Finished building."
fi
