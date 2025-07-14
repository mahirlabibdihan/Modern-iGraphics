#include "iGraphics.h"

int ball_x = 200, ball_y = 200;

void iDraw()
{
    // Clear the screen
    iClear();

    // Set drawing color Red
    iSetColor(255, 0, 0);
    iFilledCircle(ball_x, ball_y, 50);
}

void iKeyPress(unsigned char key)
{
    if (key == 'w') // Move up
    {
        ball_y += 10;
    }
    else if (key == 's') // Move down
    {
        ball_y -= 10;
    }
    else if (key == 'a') // Move left
    {
        ball_x -= 10;
    }
    else if (key == 'd') // Move right
    {
        ball_x += 10;
    }
    else if (key == 'q') // Quit the program
    {
        iExitMainLoop();
    }
}

void iSpecialKeyPress(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        ball_y += 10; // Move up
        break;
    case GLUT_KEY_DOWN:
        ball_y -= 10; // Move down
        break;
    case GLUT_KEY_LEFT:
        ball_x -= 10; // Move left
        break;
    case GLUT_KEY_RIGHT:
        ball_x += 10; // Move right
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    iWindowedMode(400, 400, "iGraphics");
    iStartMainLoop();
    return 0;
}