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
set "BASE_DIR=%~dp0MINGW"
set "PATH=%BASE_DIR%;%BASE_DIR%\bin;%PATH%"

echo Using g++ from: %BASE_DIR%

REM Set the release folder name
set "RELEASE_DIR=release\windows\x86"

REM Check if the folder exists, if so, delete it
if exist "%RELEASE_DIR%" (
    rmdir /s /q "%RELEASE_DIR%"
)

REM Create the release folder
mkdir "%RELEASE_DIR%"


:: Compile the source file to an object file (with irrKlang include path)
g++.exe -Wall -fexceptions -g -I. -IOpenGL\\include -IOpenGL\\include\\SDL2 -c "%SOURCE_FILE%" -o obj\\opengl.o

if %ERRORLEVEL% neq 0 (
   echo Compilation failed.
   exit /b 1
)

echo Compiling %SOURCE_FILE% to object file...

g++.exe -static-libgcc -static-libstdc++ -L.\\OpenGL\\lib -o "%RELEASE_DIR%\\game.exe" obj\\opengl.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lOPENGL32 -lfreeglut -lwinmm

if %ERRORLEVEL% neq 0 (
    echo Linking failed.
    exit /b 1
)

echo Finished building.

REM Copy all DLL files from bin to release folder
xcopy /y /q "bin\*.dll" "%RELEASE_DIR%\"

REM Copy the assets folder to the release folder
xcopy /e /i /y "assets" "%RELEASE_DIR%\assets"

REM Copy the assets folder to the release folder
xcopy /e /i /y "saves" "%RELEASE_DIR%\saves"

endlocal