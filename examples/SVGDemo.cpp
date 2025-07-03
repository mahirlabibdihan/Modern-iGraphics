#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/

Image tigerSVG;
void loadResources()
{
    // Load any resources needed for the application
    // For example, load images, fonts, etc.
    iLoadSVG(&tigerSVG, "assets/images/23.svg", 0.7);
}
double degree = 0.0;
void iDraw()
{
    degree++;
    // place your drawing codes here
    iClear();
    // iText(140, 180, "Hello World");

    iShowImage(100, 50, "assets/images/23.svg", 345, 559);
    iTextAdvanced(160, 140, "iShowImage", 0.4, 3);
    iShowSVG(500, 50, "assets/images/23.svg", 0.7);
    iTextAdvanced(590, 140, "iShowSVG", 0.4, 3);
    // iShowLoadedSVG(800, 50, &tigerSVG);
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key, int state)
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

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadResources(); // Load resources before initializing graphics
    iInitialize(1000, 800, "SVG Demo");
    return 0;
}