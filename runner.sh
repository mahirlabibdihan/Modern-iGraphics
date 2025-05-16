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
    # Compile the source file to an object file
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 -c "$SOURCE_FILE" -o obj/object.o

    # Link the object file to create the executable
    g++ -o bin/opengl obj/object.o -lGL -lGLU -lglut -pthread -lSDL2 -lSDL2main -lSDL2_mixer

    echo "Finished building."

    ./bin/opengl
else
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 "$SOURCE_FILE" -o bin/opengl.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut
    echo "Finished building."
    ./bin/opengl.exe
fi
# g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 iMain.cpp -o bin/opengl.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut && ./bin/opengl.exe



# Run the executable
