#include "iGraphics.h"

double scale = 1.0;
void iDraw()
{
    // place your drawing codes here
    iClear();

    iScale(450, 450, scale, scale);
    iShowImage(200, 100, "assets/images/mario.png");
    iUnScale();
}

void iMouseWheel(int dir, int x, int y)
{
    if (dir < 0 && scale > 0.1) // Zoom out
    {
        scale *= 0.9;
    }
    else if (dir > 0 && scale < 5.0) // Zoom in
    {
        scale *= 1.1;
    }
}

int main(int argc, char *argv[])
{
    iWindowedMode(900, 900, "ZoomDemo");
    iStartMainLoop();
    return 0;
}