#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    iText(120, 180, "Hello World");
}

/*
function iMouseClick() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
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
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case 'q':
        iCloseWindow();
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

void iStart()
{
    // Write your initialization codes here
    iOpenWindow(400, 400, "iGraphics");
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // Register Callbacks
    iSetDrawCallback(iDraw);
    iSetKeyboardCallback(iKeyboard);
    iSetSpecialKeyboardCallback(iSpecialKeyboard);
    iSetMouseClickCallback(iMouseClick);
    // iSetMouseMoveCallback(iMouseMove); // Optional, if you want to track mouse movement
    // iSetMouseDragCallback(iMouseDrag); // Optional, if you want to track mouse dragging
    // iSetMouseWheelCallback(iMouseWheel); // Optional, if you want to track mouse scrolling
    iStart();
    return 0;
}