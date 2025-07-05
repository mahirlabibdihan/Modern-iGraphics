#include "iGraphics.h"
#include "iFont.h"
/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    iSetColor(0, 255, 0);
    iShowText(150, 70, "Hello OpenGL!", "assets/fonts/arial.ttf", 48);
    iSetColor(0, 0, 255);
    iShowText(100, 200, "Hello OpenGL!", "assets/fonts/Antonio-Bold.ttf", 32);
    iSetColor(255, 0, 0);
    iShowText(50, 300, "Hello OpenGL!", "assets/fonts/DancingScript-Medium.ttf", 64);
    iSetColor(255, 255, 0);
    iShowText(200, 400, "Hello OpenGL!", "assets/fonts/RubikDoodleShadow-Regular.ttf", 72);
    iSetColor(255, 0, 255);
    iShowText(300, 250, "Hello OpenGL!", "assets/fonts/Monoton-Regular.ttf", 36);
    iSetColor(0, 255, 255);
    iShowText(220, 120, "Hello OpenGL!", "assets/fonts/Sixtyfour-Regular-VariableFont_BLED,SCAN.ttf", 48);
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
    case 'q':
        // do something with 'q'
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
    iInitializeFont();
    iOpenWindow(800, 500, "Text Demo");
    return 0;
}