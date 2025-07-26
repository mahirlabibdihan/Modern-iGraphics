@echo off
setlocal enabledelayedexpansion

REM Set the release folder name
set "RELEASE_DIR=release"

echo Creating release package...

REM Check if the folder exists, if so, delete it
if exist "%RELEASE_DIR%" (
    echo Removing existing release folder...
    rmdir /s /q "%RELEASE_DIR%"
)

REM Create the release folder
echo Creating release folder...
mkdir "%RELEASE_DIR%"

REM Copy all files from bin to release folder
if exist "bin\" (
    echo Copying binary files...
    xcopy /y /q "bin\*" "%RELEASE_DIR%\"
) else (
    echo Warning: bin folder not found
)

REM Copy everything except excluded folders and files using robocopy
echo Copying project files...
robocopy "." "%RELEASE_DIR%" /e ^
    /xd release examples demo MINGW .vscode .github .git bin obj OpenGL tests ^
    /xf *.bat *.cbp *.h *.cpp *.depend *.layout *.sh .gitignore banner.svg README.md *.py .gitattributes

REM robocopy returns different exit codes, so check if it worked
if %errorlevel% leq 7 (
    echo Release package created successfully in %RELEASE_DIR%\
) else (
    echo Error creating release package
)

echo Contents of release folder:
dir /b "%RELEASE_DIR%"

endlocal