#include "iGraphics.h"

int ball_x = 200, ball_y = 200;
int mouse_x = 0, mouse_y = 0;
int scroll_y = 350;
void iDraw()
{
    // Clear the screen
    iClear();

    // Set drawing color Red
    iSetColor(255, 0, 0);
    iFilledCircle(ball_x, ball_y, 10);

    iSetColor(255, 255, 255);
    char buffer[100];
    sprintf(buffer, "(%d, %d)", mouse_x, mouse_y);
    iText(mouse_x + 10, mouse_y + 10, buffer);

    iSetColor(150, 150, 150);
    iFilledRectangle(380, scroll_y, 20, 50);
    iSetColor(250, 250, 250);
    iLine(380, 0, 380, iScreenHeight);
}

void iMouseClick(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ball_x = mx;
        ball_y = my;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // Right click to reset position
        ball_x = 200;
        ball_y = 200;
    }
}

void iMouseMove(int mx, int my)
{
    mouse_x = mx;
    mouse_y = my;
}

void iMouseDrag(int mx, int my)
{
    mouse_x = ball_x = mx;
    mouse_y = ball_y = my;
}

void iMouseWheel(int dir, int x, int y)
{
    if (dir < 0) // Scroll up
    {
        // ball_x += 5;
        if (scroll_y > 0)
        {
            ball_y += 5;
            scroll_y -= 5; // Move camera up
        }
    }
    else // Scroll down
    {
        // ball_x -= 5;
        if (scroll_y < iScreenHeight - 50)
        {
            scroll_y += 5; // Move camera down
            ball_y -= 5;
        }
    }
}

int main(int argc, char *argv[])
{
    iWindowedMode(400, 400, "iGraphics");
    iStartMainLoop();
    return 0;
}