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
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 -IOpenGL/include/Freetype -c "$SOURCE_FILE" -o obj/object.o

    # Link the object file to create the executable
    g++ -o bin/iGraphics obj/object.o -lGL -lGLU -lglut -pthread -lSDL2 -lSDL2main -lSDL2_mixer -lfreetype

    echo "Finished building."

    ./bin/iGraphics
else
    g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 -IOpenGL/include/Freetype "$SOURCE_FILE" -o bin/iGraphics.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut -lfreetype
    echo "Finished building."
    ./bin/iGraphics.exe
fi
# g++ -w -fexceptions -g -I. -IOpenGL/include -IOpenGL/include/SDL2 iMain.cpp -o bin/iGraphics.exe -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOpenGL32 -lfreeglut && ./bin/iGraphics.exe



# Run the executable