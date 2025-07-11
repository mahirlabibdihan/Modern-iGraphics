#include "iGraphics.h"
#include <iostream>
using namespace std;

int bgSoundIdx = -1;

void iDraw()
{
	// place your drawing codes here
	iClear();
	iText(15, 200, "Left click to hear a chime", GLUT_BITMAP_TIMES_ROMAN_24);
}

/*
	function iMouseClick() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PlaySound("assets/sounds/chime.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

int main(int argc, char *argv[])
{
	iOpenWindow(600, 250, "Sound Demo");
	return 0;
}