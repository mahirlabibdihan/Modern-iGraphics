#include "iGraphics.h"

int ball_x, ball_y;
int dx = 5, dy = 7;
int ball_radius = 7;

/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here

    iClear();

    iSetColor(255, 100, 10);
    iFilledCircle(ball_x, ball_y, ball_radius);

    iSetColor(255, 255, 255);
    iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
    function iKeyPress() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    if (key == 'p')
    {
        // do something with 'q'
        iPauseTimer(0);
    }
    if (key == 'r')
    {
        iResumeTimer(0);
    }
    // place your codes for other keys here
}

/*
    function iSpecialKeyPress() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyPress(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    // place your codes for other keys here
}

void ballChange()
{
    ball_x += dx;
    ball_y += dy;

    if (ball_x + ball_radius > iScreenWidth || ball_x - ball_radius < 0)
    {
        if (ball_x + ball_radius > iScreenWidth)
            ball_x = iScreenWidth - ball_radius;
        else
            ball_x = ball_radius;
        dx = -dx;
    }

    if (ball_y + ball_radius > iScreenHeight || ball_y - ball_radius < 0)
    {
        if (ball_y + ball_radius > iScreenHeight)
            ball_y = iScreenHeight - ball_radius;
        else
            ball_y = ball_radius;
        dy = -dy;
    }
}

void randomizeBallPosition()
{
    ball_x = rand() % (iScreenWidth - 2 * ball_radius) + ball_radius;
    ball_y = rand() % (iScreenHeight - 2 * ball_radius) + ball_radius;
}

int main(int argc, char *argv[])
{
    iSetTimer(20, ballChange);
    // iSetTimer(2000, randomizeBallPosition);
    iOpenWindow(400, 400, "Ball Demo");
    return 0;
}