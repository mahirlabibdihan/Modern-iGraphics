#include "iGraphics.h"

// If program runs properly, it should create a window with the title "iGraphics" and dimensions 800x600. The background should be white.
void iDraw()
{
    // Clear the screen
    iClear();

    // Set drawing color Red
    iSetColor(255, 0, 0);

    // Draw text at (160, 190) position
    iText(160, 190, "Hello World");
}
int main(int argc, char *argv[])
{
    iWindowedMode(400, 400, "iGraphics");
    iStartMainLoop();
    return 0;
}