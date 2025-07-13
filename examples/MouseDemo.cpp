#include "iGraphics.h"

void iDraw()
{
	// place your drawing codes here
	iClear();
	iText(10, 10, "Move the mouse cursor to see real-time coordinates", GLUT_BITMAP_HELVETICA_12);
}

/*
	function iMouseMove() is called automatically when the mouse pointer is in motion
*/
void iMouseMove(int mx, int my)
{
	// place your code here
	printf("x = %d, y = %d\n", mx, my);
}

/*
	function iMouseClick() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iMouseWheel(int dir, int mx, int my)
{
	if (dir == 1)
	{
		printf("Mouse wheel moved up\n");
	}
	else
	{
		printf("Mouse wheel moved down\n");
	}
	return;
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

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}

	// place your codes for other keys here
}

int main(int argc, char *argv[])
{
	iOpenWindow(600, 400, "Mousedemo");
	return 0;
}