/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
#include "iGraphics.h"

Image frames[24];
Sprite sprite;

void loadResources()
{
	iInitSprite(&sprite);
	iLoadFramesFromFolder(frames, "assets/images/sprites/Golem_2/Walking");
	iChangeSpriteFrames(&sprite, frames, 24);
	iSetSpritePosition(&sprite, -200, -110);
}

void iAnim()
{
	iAnimateSprite(&sprite);
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	// place your drawing codes here
	iClear();
	{
		iSetColor(55, 55, 55);
		iFilledRectangle(0, 0, 800, 800);
	}

	iShowSprite(&sprite);

	{
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, 800, 32);
		iSetColor(0, 0, 0);
		iTextBold(10, 10, "Press arrow keys to move the sprite", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	// place your codes here
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
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
	// place your code here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'x')
	{
		// do something with 'x'
		exit(0);
	}
	// place your codes for other keys here
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

int direction = 1;
void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (direction == 1)
		{
			iMirrorSprite(&sprite, HORIZONTAL);
			direction = -1;
		}
		else
		{
			sprite.x -= 2;
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (direction == -1)
		{
			iMirrorSprite(&sprite, HORIZONTAL);
			direction = 1;
		}
		else
		{
			sprite.x += 2;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		sprite.y++;
	}
	if (key == GLUT_KEY_DOWN)
	{
		sprite.y--;
	}
	// place your codes for other keys here
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	loadResources();
	iSetTimer(100, iAnim);
	iInitialize(800, 800, "SpriteDemo");
	return 0;
}
