#include "iGraphics.h"

// This program draws a simple house with a shining sun in the sky.
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

double roof_x[] = {300, 200, 400};
double roof_y[] = {600, 500, 500};

int wall_x = 200, wall_y = 300, wall_dx = 200, wall_dy = 200;
int door_x = 300, door_y = 300, door_dx = 50, door_dy = 100;
int window_x = 225, window_y = 400, window_dx = 50, window_dy = 50;
int sun_x = 500, sun_y = 700, sun_r = 50;

/*
        function iDraw() is called again and again by the system.
*/

void drawCoordinateAxes(double gap = 50.0, int r = 0, int g = 0, int b = 0)
{
    iSetColor(r, g, b);

    for (int i = 0; i < SCREEN_WIDTH; i += gap)
    {
        iLine(i, 0, i, SCREEN_HEIGHT);

        if (i % (int)gap == 0)
        {
            char *str = (char *)malloc(10);
            sprintf(str, "%d", i);
            iText(i + 5, 5, str);
            free(str);
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i += gap)
    {
        iLine(0, i, SCREEN_WIDTH, i);

        if (i % (int)gap == 0)
        {
            char *str = (char *)malloc(10);
            sprintf(str, "%d", i);
            iText(5, i + 5, str);
            free(str);
        }
    }
}

void drawSunRays()
{
    iSetColor(255, 0, 0);
    double angle = 0;
    double pi = 3.1416;
    int rayLength = sun_r + 20;
    for (int i = 0; i < 30; i++)
    {
        iLine(sun_x + sun_r * sin(angle), sun_y + sun_r * cos(angle), sun_x + rayLength * sin(angle), sun_y + rayLength * cos(angle));
        angle += pi / 15;
    }
}

void iDraw()
{
    iClear();
    // place your drawing codes here

    // set sky color
    iSetColor(135, 206, 235);
    iFilledRectangle(0, 400, 600, 400);

    // set ground color
    iSetColor(180, 180, 180);
    iFilledRectangle(0, 0, 600, 400);

    iSetColor(0, 255, 0);
    iFilledPolygon(roof_x, roof_y, 3);

    iSetColor(255, 0, 0);
    iFilledRectangle(wall_x, wall_y, wall_dx, wall_dy);

    iSetColor(0, 0, 255);
    iFilledRectangle(door_x, door_y, door_dx, door_dy);

    iSetColor(255, 255, 0);
    iFilledRectangle(window_x, window_y, window_dx, window_dy);

    iSetColor(255, 255, 0);
    iFilledCircle(sun_x, sun_y, sun_r);
    drawSunRays();

    // drawCoordinateAxes(50.0);
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
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
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
void iKeyboard(unsigned char key)
{
    if (key == 'q')
    {
        exit(0);
    }
    // place your codes for other keys here
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

    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Demo!");
    return 0;
}
