@echo off
setlocal

:: Set default source file if not provided
if "%~1"=="" (
    set "SOURCE_FILE=iMain.cpp"
    echo No input file specified. Using default: iMain.cpp
) else (
    set "SOURCE_FILE=%~1"
)

:: Set the base directory for g++ (optional if g++ is in your PATH)
set BASE_DIR=C:\MINGW
set PATH=%BASE_DIR%;%BASE_DIR%\bin;%PATH%

:: Compile the source file to an object file (with irrKlang include path)
g++.exe -Wall -fexceptions -g -IOpenGL\include -IOpenGL\include\irrKlang -c "%SOURCE_FILE%" -o obj\object.o
if %ERRORLEVEL% neq 0 (
    echo Compilation failed.
    exit /b 1
)

:: Link the object file to create the executable (with irrKlang lib)
g++.exe -static -static-libgcc -static-libstdc++ -L.\OpenGL\lib -o bin\opengl.exe obj\object.o OpenGL\lib\GLU32.LIB OpenGL\lib\OPENGL32.LIB -lGLU32 -lfreeglut -lOPENGL32 -lgdi32 -lwinmm -lirrKlang
if %ERRORLEVEL% neq 0 (
    echo Linking failed.
    exit /b 1
)

echo Finished building.

bin\opengl.exe
endlocal
