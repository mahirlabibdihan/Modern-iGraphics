#include "iGraphics.h"

void iDraw()
{
	// place your drawing codes here
	iClear();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			iScale(15 + i * 100, j * 100, 0.15, 0.15);
			iShowImage(15 + i * 100, j * 100, "assets/images/mario.png");
			iUnScale();
		}
	}

	for (int i = 4; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			iScale(15 + i * 100, j * 100, 0.8, 0.8);
			iShowImage(15 + i * 100, j * 100, "assets/images/smurf.bmp");
			iUnScale();
		}
	}
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
	iWindowedMode(800, 800, "ImageDemo");
	iStartMainLoop();
	return 0;
}