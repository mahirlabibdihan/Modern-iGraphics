@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM Check if filename argument is provided
if "%~1"=="" (
    echo 📋 Usage: create_project.bat ^<filename^>
    echo 💡 Example: create_project.bat MyGame
    echo.
    echo 🎯 This will create MyGame.cpp with iGraphics starter code
    pause
    exit /b 1
)

set "filename=%~1"

echo 🚀 Creating project file for: %filename%

REM Remove .cpp extension if provided
if "%filename:~-4%"==".cpp" (
    set "filename=%filename:~0,-4%"
)

set "output_file=%filename%.cpp"

echo 📁 Output file will be: %output_file%

REM Check if file already exists
if exist "%output_file%" (
    echo ⚠️  Error: File "%output_file%" already exists!
    echo 🔄 Overwriting existing file...
)

echo ✨ Creating "%output_file%"...

(
echo #include "iGraphics.h"
echo.
echo // Global variables
echo int screenWidth = 800;
echo int screenHeight = 600;
echo.
echo // Game state variables
echo // Add your variables here
echo.
echo /*
echo  * iDraw^(^) is called repeatedly by the system.
echo  * Place your drawing code here.
echo  */
echo void iDraw^(^)
echo {
echo     // Clear the screen
echo     iClear^(^);
echo.
echo     // Set drawing color ^(Red, Green, Blue^)
echo     iSetColor^(255, 255, 255^);
echo.
echo     // Draw your graphics here
echo     iText^(50, screenHeight - 50, "Hello, iGraphics!"^);
echo     iText^(50, screenHeight - 80, "Press 'q' to quit, 'f' for fullscreen"^);
echo.
echo     // Example: Draw a circle
echo     iSetColor^(255, 0, 0^);
echo     iFilledCircle^(screenWidth/2, screenHeight/2, 50^);
echo }
echo.
echo /*
echo  * iMouseClick^(^) is called when mouse is clicked.
echo  * button: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
echo  * state: GLUT_DOWN, GLUT_UP
echo  * mx, my: mouse coordinates
echo  */
echo void iMouseClick^(int button, int state, int mx, int my^)
echo {
echo     if ^(button == GLUT_LEFT_BUTTON ^&^& state == GLUT_DOWN^)
echo     {
echo         // Left mouse button pressed
echo         printf^("Mouse clicked at: %%d, %%d\n", mx, my^);
echo     }
echo }
echo.
echo /*
echo  * iMouseMove^(^) is called when mouse moves.
echo  * mx, my: mouse coordinates
echo  */
echo void iMouseMove^(int mx, int my^)
echo {
echo     // Mouse move code here
echo }
echo.
echo /*
echo  * iKeyPress^(^) is called when a regular key is pressed.
echo  * key: ASCII value of the key
echo  */
echo void iKeyPress^(unsigned char key^)
echo {
echo     switch ^(key^)
echo     {
echo     case 'q':
echo     case 'Q':
echo         iCloseWindow^(^);
echo         break;
echo     case 'f':
echo     case 'F':
echo         iToggleFullscreen^(^);
echo         break;
echo     case ' ':
echo         // Space key pressed
echo         break;
echo     default:
echo         printf^("Key pressed: %%c (ASCII: %%d)\n", key, key^);
echo         break;
echo     }
echo }
echo.
echo /*
echo  * iSpecialKeyPress^(^) is called when special keys are pressed.
echo  * Available keys: GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT,
echo  * GLUT_KEY_F1-F12, GLUT_KEY_HOME, GLUT_KEY_END, etc.
echo  */
echo void iSpecialKeyPress^(unsigned char key^)
echo {
echo     switch ^(key^)
echo     {
echo     case GLUT_KEY_UP:
echo         // Up arrow pressed
echo         break;
echo     case GLUT_KEY_DOWN:
echo         // Down arrow pressed
echo         break;
echo     case GLUT_KEY_LEFT:
echo         // Left arrow pressed
echo         break;
echo     case GLUT_KEY_RIGHT:
echo         // Right arrow pressed
echo         break;
echo     case GLUT_KEY_END:
echo         iCloseWindow^(^);
echo         break;
echo     default:
echo         break;
echo     }
echo }
echo.
echo /*
echo  * Animation timer function.
echo  * This function is called repeatedly for animations.
echo  * dt: time difference in milliseconds since last call
echo  */
echo void iAnimation^(^)
echo {
echo     // Animation code here
echo     // For example: update positions, change colors, etc.
echo }
echo.
echo /*
echo  * Main function - Entry point of the program
echo  */
echo int main^(int argc, char *argv[]^)
echo {
echo     // Initialize any resources here
echo     // For example: load images, sounds, etc.
echo.
echo     // Set up animation timer ^(optional^)
echo     // iSetTimer^(16, iAnimation^); // ~60 FPS
echo.
echo     // Set the screen dimensions
echo     iWindowedMode^(screenWidth, screenHeight, "%filename%"^);
echo.
echo     // Enter into the main loop
echo.    iStartMainLoop^(^);
echo     return 0;
echo }
) > "%output_file%"

echo.
echo ✅ Successfully created "%output_file%"!
echo.
echo 🔨 To compile and run: .\runner.bat %output_file%
echo.
echo 🎉 Happy coding with iGraphics!
echo.
