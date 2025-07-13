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
	function iKeyPress() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
	if (key == 'x')
	{
		// do something with 'x'
		exit(0);
	}
	// place your codes for other keys here
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

int direction = 1;
void iSpecialKeyPress(unsigned char key)
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
	loadResources();
	iSetTimer(100, iAnim);
	iOpenWindow(800, 800, "SpriteDemo");
	return 0;
}