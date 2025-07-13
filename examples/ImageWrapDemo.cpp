#include "iGraphics.h"

Image bg;
int speed = 2;

void loadResources()
{
	iLoadImage(&bg, "assets/images/background.jpg");
	iResizeImage(&bg, 900, 450);
}

void iDraw()
{
	// place your drawing codes here
	//  load background.jpg using stb_image
	if (!isFullScreen)
		iToggleFullscreen();
	iClear();
	iShowLoadedImage(0, 0, &bg);
	iWrapImage(&bg, speed);
	iText(70, 50, "Press LEFT to decrease speed, RIGHT to increase speed", GLUT_BITMAP_TIMES_ROMAN_24);
}

/*
	function iMouseClick() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		iToggleFullscreen();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
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

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (speed > 0)
			speed--;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		speed++;
	}

	// place your codes for other keys here
}

int main(int argc, char *argv[])
{
	loadResources();
	iOpenWindow(900, 450, "ImageWrapDemo");
	return 0;
}