#include "iGraphics.h"

double ball_x_1 = 100, ball_y_1 = 200;
double ball_x_2 = 300, ball_y_2 = 200;
double vy_1 = -150, vy_2 = -150;
double vx_1 = 0, vx_2 = 0;
double ball_radius = 20;

/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();

    iShowImage(0, 0, "assets/images/background.jpg");
    iScale(165, 100, 0.15, 0.15);
    iShowImage(165, 100, "assets/images/mario.png");
    iUnScale();

    iSetColor(0, 0, 0);
    iSetLineWidth(2.0);
    iLine(ball_x_1, ball_y_1, ball_x_2, ball_y_2);

    iSetColor(255, 100, 10);
    iFilledCircle(ball_x_1, ball_y_1, ball_radius);
    iSetColor(0, 0, 0);
    iCircle(ball_x_1, ball_y_1, ball_radius);

    iSetColor(100, 10, 255);
    iFilledCircle(ball_x_2, ball_y_2, ball_radius);
    iSetColor(0, 0, 0);
    iCircle(ball_x_2, ball_y_2, ball_radius);
}

void ballChange1()
{
    // s = vt
    ball_y_1 += vy_1 * 20 / 1000.0; // 20 is the time step in milliseconds
    ball_x_1 += vx_1 * 20 / 1000.0;

    if (ball_x_1 + ball_radius > iScreenWidth || ball_x_1 - ball_radius < 0)
    {
        if (ball_x_1 + ball_radius > iScreenWidth)
            ball_x_1 = iScreenWidth - ball_radius;
        else
            ball_x_1 = ball_radius;
        vx_1 = -vx_1;
    }

    if (ball_y_1 + ball_radius > iScreenHeight || ball_y_1 - ball_radius < 0)
    {
        if (ball_y_1 + ball_radius > iScreenHeight)
            ball_y_1 = iScreenHeight - ball_radius;
        else
            ball_y_1 = ball_radius;
        vy_1 = -vy_1;
    }
}

void ballChange2(int dt)
{
    // s = vt
    ball_y_2 += vy_2 * dt / 1000.0;
    ball_x_2 += vx_2 * dt / 1000.0;

    if (ball_x_2 + ball_radius > iScreenWidth || ball_x_2 - ball_radius < 0)
    {
        if (ball_x_2 + ball_radius > iScreenWidth)
            ball_x_2 = iScreenWidth - ball_radius;
        else
            ball_x_2 = ball_radius;
        vx_2 = -vx_2;
    }

    if (ball_y_2 + ball_radius > iScreenHeight || ball_y_2 - ball_radius < 0)
    {
        if (ball_y_2 + ball_radius > iScreenHeight)
            ball_y_2 = iScreenHeight - ball_radius;
        else
            ball_y_2 = ball_radius;
        vy_2 = -vy_2;
    }
}

int main(int argc, char *argv[])
{
    iSetTimer(20, ballChange1);
    iSetAdvancedTimer(20, ballChange2);
    iOpenWindow(400, 350, "Ball Demo");
    return 0;
}