#include "iGraphics.h"

// If program runs properly, it should create a window with the title "iGraphics" and dimensions 800x600. The background should be white.
int main(int argc, char *argv[])
{
    iWindowedMode(800, 600, "iGraphics");
    iStartMainLoop();
    return 0;
}