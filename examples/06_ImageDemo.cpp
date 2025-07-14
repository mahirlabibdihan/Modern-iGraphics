#include "iGraphics.h"

void iDraw()
{
	// place your drawing codes here
	iClear();
	iShowImage(200, 100, "assets/images/mario.png");
}

void iKeyPress(unsigned char key)
{
	if (key == 'q')
	{
		iExitMainLoop();
	}
}

int main(int argc, char *argv[])
{
	iWindowedMode(900, 900, "ImageDemo");
	iStartMainLoop();
	return 0;
}