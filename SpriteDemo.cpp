#include "iGraphics.h"



Sprite bg, mario1, mario2;

void loadResources()
{
    iLoadSprite(&bg, "background.jpg", -1);
    iSetSpritePosition(&bg, 200, 200);
    iLoadSprite(&mario1, "mario.png", 0);
    iSetSpritePosition(&mario1, 411, 304);
    double marioAspectRatio = (double)mario1.img.width / mario1.img.height;
    iResizeSprite(&mario1, 48, 48.0 / marioAspectRatio);

    iLoadSprite(&mario2, "mario.png", 0);
    iResizeSprite(&mario2, 200, 200.0 / marioAspectRatio);
    iSetSpritePosition(&mario2, 211, 304);
}

void iDraw()
{
	//place your drawing codes here	
    // load background.jpg using stb_image
	iClear();
    iShowSprite(&bg);
    iShowSprite(&mario1);
    iShowSprite(&mario2);
    if (iCheckCollision(&mario1, &mario2)) {
        iText(500, 500, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		iMirrorSprite(&mario1, HORIZONTAL);
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		iMirrorSprite(&mario1, VERTICAL);
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{

	//place your codes for other keys here
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

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
    if(key == GLUT_KEY_LEFT)
    {
        mario1.x -= 10;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        mario1.x += 10;
    }
    if(key == GLUT_KEY_UP)
    {
        mario1.y += 10;
    }
    if(key == GLUT_KEY_DOWN)
    {
        mario1.y -= 10;
    }

	//place your codes for other keys here
}

int main()
{
	loadResources();
	iInitialize(900, 900, "ImageDemp");
	return 0;
}	