#include "iGraphics.h"
#include "iFont.h"
/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    iSetColor(0, 255, 0);
    iShowText(150, 70, "Hello OpenGL!", "assets/fonts/arial.ttf", 48);
    iSetColor(0, 0, 255);
    iShowText(100, 200, "Hello OpenGL!", "assets/fonts/Antonio-Bold.ttf", 32);
    iSetColor(255, 0, 0);
    iShowText(50, 300, "Hello OpenGL!", "assets/fonts/DancingScript-Medium.ttf", 64);
    iSetColor(255, 255, 0);
    iShowText(200, 400, "Hello OpenGL!", "assets/fonts/RubikDoodleShadow-Regular.ttf", 72);
    iSetColor(255, 0, 255);
    iShowText(300, 250, "Hello OpenGL!", "assets/fonts/Monoton-Regular.ttf", 36);
    iSetColor(0, 255, 255);
    iShowText(220, 120, "Hello OpenGL!", "assets/fonts/Sixtyfour-Regular-VariableFont_BLED,SCAN.ttf", 48);
}

int main(int argc, char *argv[])
{
    iOpenWindow(800, 500, "Text Demo");
    return 0;
}