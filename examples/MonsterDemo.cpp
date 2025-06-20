/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
#include "iGraphics.h"
enum
{
	IDLE,
	WALK,
	JUMP
};
int pic_x, pic_y;
int state = IDLE;
int direction = 1; // 1 for right, -1 for left

Image idleMonster[4], walkMonster[6], jumpMonster[8];
Sprite monster;

void loadResources()
{
	iLoadFramesFromSheet(idleMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Idle_4.png", 1, 4);
	iLoadFramesFromSheet(walkMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Walk_6.png", 1, 6);
	iLoadFramesFromSheet(jumpMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Jump_8.png", 1, 8);

	iInitSprite(&monster, -1);
	iChangeSpriteFrames(&monster, idleMonster, 4);
	iSetSpritePosition(&monster, 20, 0);
	iScaleSprite(&monster, 3.0);
}

void updateMonster()
{
	switch (state)
	{
	case IDLE:
		break;
	case WALK:
		break;
	case JUMP:
		if (monster.y == 0)
		{
			state = IDLE;
			iChangeSpriteFrames(&monster, idleMonster, 4);
		}
		break;
	}
	iAnimateSprite(&monster);
	monster.y = max(0, monster.y - 1);
}
/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	// place your drawing codes here
	iClear();
	iShowSprite(&monster);
	// iShowBMP(pic_x, pic_y, "wheel.bmp");
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
			iMirrorSprite(&monster, HORIZONTAL);
			direction = -1;
		}
		else
		{
			monster.x--;
			if (state != WALK)
			{
				state = WALK;
				iChangeSpriteFrames(&monster, walkMonster, 6);
			}
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (direction == -1)
		{
			iMirrorSprite(&monster, HORIZONTAL);
			direction = 1;
		}
		else
		{
			monster.x++;
			if (state != WALK)
			{
				state = WALK;
				iChangeSpriteFrames(&monster, walkMonster, 6);
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		monster.y++;
		if (state != JUMP)
		{
			state = JUMP;
			iChangeSpriteFrames(&monster, jumpMonster, 8);
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		monster.y--;
	}
	// place your codes for other keys here
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	loadResources();
	iSetTimer(100, updateMonster);
	iInitialize(500, 400, "SpriteDemo");
	return 0;
}
