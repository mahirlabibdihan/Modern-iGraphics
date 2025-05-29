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
}

/*
	function iMouseDrag() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
	// place your codes here
}

/*
	function iMouseMove() is called automatically when the mouse pointer is in motion
*/
void iMouseMove(int mx, int my)
{
	// place your code here
	//  printf("x = %d, y = %d\n", mx, my);
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PlaySound("assets/sounds/chime.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iMouseWheel(int dir, int mx, int my)
{
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	switch (key)
	{
	case 'r':
		break;
	case 'p':
		break;
	case 'x':
		break;
		// place your codes for other keys here
	default:
		break;
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
		// place your codes for other keys here
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	iInitialize(600, 250, "Sound Demo");
	return 0;
}
