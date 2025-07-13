#include "iGraphics.h"
#include <iostream>
#include "iSound.h"
using namespace std;

int bgSoundIdx = -1;

void iDraw()
{
	// place your drawing codes here
	iClear();
	iText(15, 200, "Left click to hear a chime", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(15, 160, "Press 'p' to pause background music", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(15, 120, "Press 'r' to resume background music", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(15, 80, "Press 'x' to stop background music", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(15, 40, "Press UP/DOWN arrow keys to increase/decrease volume", GLUT_BITMAP_TIMES_ROMAN_24);
}

/*
	function iMouseClick() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		iPlaySound("assets/sounds/chime.wav", false);
		// PlaySound("chime.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

/*
	function iKeyPress() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
	switch (key)
	{
	case 'r':
		iResumeSound(bgSoundIdx);
		break;
	case 'p':
		iPauseSound(bgSoundIdx);
		break;
	case 'x':
		iStopSound(bgSoundIdx);
		break;
		// place your codes for other keys here
	default:
		break;
	}
}

/*
	function iSpecialKeyPress() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyPress(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		iIncreaseVolume(bgSoundIdx, 5);
		break;
	case GLUT_KEY_DOWN:
		iDecreaseVolume(bgSoundIdx, 5);
		break;
		// place your codes for other keys here
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	bgSoundIdx = iPlaySound("assets/sounds/bgm1.mp3", true, 50);
	iOpenWindow(600, 250, "Sound Demo");
	return 0;
}