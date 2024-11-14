@echo off
setlocal

:: Check for source file argument
if "%~1"=="" (
    echo Usage: %0 source_file
    exit /b 1
)

:: Set the Base Directory
set BASE_DIR=D:\CourseMaterials\CSE102\igraphics-demo\MinGW
:: Set the PATH
set PATH=%BASE_DIR%;%BASE_DIR%\bin;%PATH%

:: Compile the source file to an object file
g++.exe -Wall -fexceptions -g -IOpenGL\include -c "%~1" -o exec\object.o
if %ERRORLEVEL% neq 0 (
    echo Compilation failed.
    exit /b 1
)

:: Link the object file to create the executable
g++.exe -static -static-libgcc -static-libstdc++ -L.\OpenGL\lib -o exec\opengl.exe exec\object.o OpenGL\lib\Glaux.lib OpenGL\lib\GLU32.LIB OpenGL\lib\glui32.lib OpenGL\lib\glut32.lib OpenGL\lib\OPENGL32.LIB -lGlaux -lGLU32 -lglui32 -lglut32 -lOPENGL32 -lgdi32 -lwinmm
if %ERRORLEVEL% neq 0 (
    echo Linking failed.
    exit /b 1
)

echo Finished building.

exec\opengl.exe
endlocal
