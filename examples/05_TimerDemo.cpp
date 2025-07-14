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
    iText(10, 10, "Press p for pause, r for resume, q for exit.");
}

/*
    function iKeyPress() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case 'p':
        iPauseTimer(0);
        break;
    case 'r':
        iResumeTimer(0);
        break;
    case 'q':
        iExitMainLoop();
        break;
    default:
        break;
    }
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