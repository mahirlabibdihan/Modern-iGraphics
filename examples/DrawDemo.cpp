#include "iGraphics.h"

int width = 1280, height = 720;
double originX = width / 2.0, originY = height / 2.0;

void drawAxis()
{
    iSetColor(255, 255, 255);
    iLine(0, originY, width, originY);
    iLine(originX, 0, originX + 100, height);
}

void iDraw()
{
    // place your drawing codes here
    iClear();

    iSetLineWidth(4);
    drawAxis();

    iSetColor(255, 0, 0);
    iFilledRectangle(0, 0, 100, 100);
    iSetTransparentColor(0, 255, 0, 0.5);
    iFilledRectangle(50, 50, 100, 100);
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
    function iMouseMove() is called automatically when the mouse pointer is in motion
*/
void iMouseMove(int mx, int my)
{
    // place your code here
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}

void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }

    // place your codes for other keys here
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iSetTransparency(1); // To enable transparency
    iInitialize(width, height, "DrawDemo");
    return 0;
}