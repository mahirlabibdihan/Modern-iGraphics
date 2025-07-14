#include "iGraphics.h"

void iDraw()
{
    // Clear the screen
    iClear();

    // Draw rectangle
    iSetColor(0, 255, 0);               // Set color to red
    iFilledRectangle(50, 50, 200, 150); // Draw filled rectangle

    // Draw circle
    iSetColor(255, 0, 0);        // Set color to green
    iFilledCircle(150, 125, 50); // Draw filled circle

    // Draw rectangle
    iSetColor(0, 255, 0);          // Set color to red
    iRectangle(50, 250, 200, 150); // Draw filled rectangle

    // Draw circle
    iSetColor(255, 0, 0);  // Set color to green
    iCircle(150, 325, 50); // Draw filled circle

    // Draw Line
    iSetColor(0, 0, 255);    // Set color to blue
    iLine(300, 0, 300, 450); // Draw line

    // Draw Polygon
    double xx[5] = {350, 400, 450, 500, 550};
    double yy[5] = {50, 100, 50, 100, 50};
    iSetColor(255, 255, 0);    // Set color to yellow
    iFilledPolygon(xx, yy, 5); // Draw filled polygon

    double xx2[4] = {400, 450, 500};
    double yy2[4] = {150, 100, 150};
    iSetColor(0, 255, 255); // Set color to cyan
    iPolygon(xx2, yy2, 3);  // Draw filled polygon

    // Draw Ellipse
    iSetColor(255, 0, 255);            // Set color to magenta
    iFilledEllipse(450, 325, 100, 50); // Draw filled ellipse

    // Draw thick line
    iSetColor(128, 128, 128); // Set color to gray
    iSetLineWidth(5);         // Set line width
    iLine(600, 0, 600, 450);  // Draw thick line
    iSetLineWidth(2);

    iSetColor(0, 128, 0); // Set color to dark green
    double x, y;
    for (y = 0; y < 450; y += 5)
    {
        x = 800 + 100 * sin(y * 0.05);                       // Vertical sine wave formula
        iLine(x, y, 700 + 100 * sin((y + 5) * 0.05), y + 5); // Draw line segments
    }
    iSetColor(255, 255, 255); // Reset color to white
}

int main(int argc, char *argv[])
{
    iWindowedMode(900, 450, "iGraphics");
    iStartMainLoop();
    return 0;
}