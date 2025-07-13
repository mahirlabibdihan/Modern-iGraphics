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
int m_state = IDLE;
int direction = 1; // 1 for right, -1 for left

Image idleMonster[4], walkMonster[6], jumpMonster[8];
Sprite monster;

#define max(a, b) ((a) > (b) ? (a) : (b))
void loadResources()
{
	iLoadFramesFromSheet(idleMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Idle_4.png", 1, 4);
	iLoadFramesFromSheet(walkMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Walk_6.png", 1, 6);
	iLoadFramesFromSheet(jumpMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Jump_8.png", 1, 8);

	iInitSprite(&monster);
	iChangeSpriteFrames(&monster, idleMonster, 4);
	iSetSpritePosition(&monster, 20, 0);
	iScaleSprite(&monster, 3.0);
}

void updateMonster()
{
	switch (m_state)
	{
	case IDLE:
		break;
	case WALK:
		break;
	case JUMP:
		if (monster.y == 0)
		{
			m_state = IDLE;
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
			iMirrorSprite(&monster, HORIZONTAL);
			direction = -1;
		}
		else
		{
			monster.x--;
			if (m_state != WALK)
			{
				m_state = WALK;
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
			if (m_state != WALK)
			{
				m_state = WALK;
				iChangeSpriteFrames(&monster, walkMonster, 6);
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		monster.y++;
		if (m_state != JUMP)
		{
			m_state = JUMP;
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
	loadResources();
	iSetTimer(100, updateMonster);
	iOpenWindow(500, 400, "SpriteDemo");
	return 0;
}