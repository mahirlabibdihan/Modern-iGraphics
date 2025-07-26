#include "iGraphics.h"

Image mario1, mario2;
int x, y;

void loadImages()
{
    iLoadImage(&mario1, "assets/images/mario.png");
    iScaleImage(&mario1, 0.15);
    x = 15;
    y = 0;
    iLoadImage(&mario2, "assets/images/mario.png");
    iScaleImage(&mario2, 0.15);
    iMirrorImage(&mario2, HORIZONTAL);
}
void iDraw()
{
    // place your drawing codes here
    iClear();

    iShowLoadedImage(x, y, &mario1);
    iShowLoadedImage(400, 0, &mario2);

    if (iCheckImageCollision(x, y, &mario1, 400, 0, &mario2))
    {
        iSetColor(255, 0, 0);
        iText(10, 10, "Collision Detected!", GLUT_BITMAP_HELVETICA_12);
    }
}

void iKeyPress(unsigned char key)
{
    if (key == 'q')
    {
        iExitMainLoop();
    }
}

void iSpecialKeyPress(unsigned char key)
{
    if (key == GLUT_KEY_LEFT)
    {
        x -= 10;
        iMirrorImage(&mario1, HORIZONTAL);
    }
    if (key == GLUT_KEY_RIGHT)
    {
        x += 10;
        iMirrorImage(&mario1, HORIZONTAL);
    }
    if (key == GLUT_KEY_UP)
    {
        y += 10;
    }
    if (key == GLUT_KEY_DOWN)
    {
        y -= 10;
    }
}

int main(int argc, char *argv[])
{
    iWindowedMode(800, 800, "ImageDemo");
    loadImages();
    iStartMainLoop();
    return 0;
}