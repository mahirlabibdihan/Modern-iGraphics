#include "iGraphics.h"
#include "iSound.h"
Image bg;

Sprite mario1, mario2, rect;
Image pinkMonsterFrames[4], golemFrames[24];
Image rectFrame;
Sprite pinkMonster, golem;
bool isMirroredX[2] = {false, false};
#define PINK_MONSTER 0
#define GOLEM 1

void loadResources()
{
    iLoadFramesFromSheet(pinkMonsterFrames, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Idle_4.png", 1, 4);
    iInitSprite(&pinkMonster, -1);
    iChangeSpriteFrames(&pinkMonster, pinkMonsterFrames, 4);
    iSetSpritePosition(&pinkMonster, 300, 250);
    iScaleSprite(&pinkMonster, 3.0);

    iLoadFramesFromFolder(golemFrames, "assets/images/sprites/Golem_2/Walking");
    iInitSprite(&golem, -1);
    iChangeSpriteFrames(&golem, golemFrames, 24);
    iSetSpritePosition(&golem, 300, 200);
    iScaleSprite(&golem, 0.5);

    iLoadImage(&bg, "assets/images/background.jpg");
    iResizeImage(&bg, 1800, 1000);

    iLoadImage(&rectFrame, "assets/images/rect.png"); // Ignore white color for collision detection
    iInitSprite(&rect, 0xFFFFFF);
    iChangeSpriteFrames(&rect, &rectFrame, 1);
    iSetSpritePosition(&rect, -100, -50);
    iScaleSprite(&rect, 2);
    // iWrapSprite(&rect, 500);
}

void iDraw()
{
    // place your drawing codes here

    // iShowSprite(&mario1);
    iShowLoadedImage(0, 0, &bg);
    iWrapImage(&bg, -10);
    iShowSprite(&golem);
    iShowSprite(&pinkMonster);
    // iShowSprite(&mario2);
    if (iCheckCollision(&rect, &golem))
    {
        iText(500, 100, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    iShowSprite(&rect);
    // if (iCheckCollision(&mario1, &rect))
    // {
    //     iText(100, 500, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
    // }
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
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        iMirrorSprite(&pinkMonster, HORIZONTAL);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        iMirrorSprite(&pinkMonster, VERTICAL);
    }
}

void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

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
        if (!isMirroredX[GOLEM])
        {
            iMirrorSprite(&golem, HORIZONTAL);
            isMirroredX[GOLEM] = true;
        }
        golem.x -= 10;
        if (iCheckCollision(&golem, &rect))
        {
            golem.x += 10;
        }
    }
    if (key == GLUT_KEY_RIGHT)
    {
        if (isMirroredX[GOLEM])
        {
            iMirrorSprite(&golem, HORIZONTAL);
            isMirroredX[GOLEM] = false;
        }
        golem.x += 10;
        if (iCheckCollision(&golem, &rect))
        {
            golem.x -= 10;
        }
    }
    if (key == GLUT_KEY_UP)
    {
        golem.y += 10;
        if (iCheckCollision(&golem, &rect))
        {
            golem.y -= 10;
        }
    }
    if (key == GLUT_KEY_DOWN)
    {
        golem.y -= 10;
        if (iCheckCollision(&golem, &rect))
        {
            golem.y += 10;
        }
    }

    // place your codes for other keys here
}

void iAnim()
{
    // place your codes here
    iAnimateSprite(&golem);
    iAnimateSprite(&pinkMonster);
    // iUpdateSprite(&mario1);
    // iUpdateSprite(&mario2);
    // iUpdateSprite(&rect);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadResources();
    iInitializeSound();
    iPlaySound("assets/sounds/background.wav", true);
    iSetTimer(50, iAnim);
    iInitialize(1800, 1000, "Sprite Demo");
    return 0;
}