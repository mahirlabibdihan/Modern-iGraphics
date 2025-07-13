#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/

Image tigerSVG, tigerImg;
void loadResources()
{
    // Load any resources needed for the application
    // For example, load images, fonts, etc.
    iLoadImage(&tigerImg, "assets/images/23.svg");
    iScaleImage(&tigerImg, 0.7);
}

void iDraw()
{
    // place your drawing codes here
    iClear();
    iShowLoadedImage(100, 50, &tigerImg);
}

/*
function iKeyPress() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case 'h':
        iHideCursor(); // Show the cursor
        break;
    case 's':
        iShowCursor(); // Hide the cursor
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    loadResources(); // Load resources before initializing graphics
    iOpenWindow(1000, 800, "SVG Demo");
    return 0;
}