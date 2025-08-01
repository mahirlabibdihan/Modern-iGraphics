#include "iGraphics.h"

#define min(a, b) a > b ? b : a
#define max(a, b) a < b ? b : a

int ball_1_x = 200, ball_1_y = 200;
int ball_2_x = 300, ball_2_y = 300;

int ball_radius = 20;
int dir_1_x = 0, dir_1_y = 0;
int dir_2_x = 0, dir_2_y = 0;

void iDraw()
{
    // Clear the screen
    iClear();

    iSetColor(255, 255, 255);
    iFilledRectangle(0, 0, iScreenWidth, iScreenHeight);
    // Set drawing color Red
    iSetTransparentColor(255, 0, 0, 0.5);
    iFilledCircle(ball_1_x, ball_1_y, ball_radius);

    // Set drawing color Blue
    iSetTransparentColor(0, 0, 255, 0.5);
    iFilledCircle(ball_2_x, ball_2_y, ball_radius);
}

void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case 'w': // Move up
        dir_1_y = 1;
        break;
    case 's': // Move down
        dir_1_y = -1;
        break;
    case 'a': // Move left
        dir_1_x = -1;
        break;
    case 'd': // Move right
        dir_1_x = 1;
        break;
    case 'q': // Quit the program
        iExitMainLoop();
        break;
    default:
        break;
    }
}

void iKeyRelease(unsigned char key)
{
    switch (key)
    {
    case 'w':
    case 's':
        dir_1_y = 0;
        break;
    case 'a':
    case 'd':
        dir_1_x = 0;
        break;
    default:
        break;
    }
}

void iSpecialKeyPress(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        dir_2_y = 1;
        break;
    case GLUT_KEY_DOWN:
        dir_2_y = -1;
        break;
    case GLUT_KEY_LEFT:
        dir_2_x = -1;
        break;
    case GLUT_KEY_RIGHT:
        dir_2_x = 1;
        break;
    default:
        break;
    }
}

void iSpecialKeyRelease(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        dir_2_y = 0;
        break;
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        dir_2_x = 0;
        break;
    default:
        break;
    }
}

void ballMovement()
{
    ball_1_x = max(min(ball_1_x + dir_1_x * 10, iScreenWidth - ball_radius), ball_radius);
    ball_1_y = max(min(ball_1_y + dir_1_y * 10, iScreenHeight - ball_radius), ball_radius);

    ball_2_x = max(min(ball_2_x + dir_2_x * 10, iScreenWidth - ball_radius), ball_radius);
    ball_2_y = max(min(ball_2_y + dir_2_y * 10, iScreenHeight - ball_radius), ball_radius);
}

int main(int argc, char *argv[])
{
    iSetTimer(20, ballMovement);
    iWindowedMode(400, 400, "iGraphics");
    iStartMainLoop();
    return 0;
}