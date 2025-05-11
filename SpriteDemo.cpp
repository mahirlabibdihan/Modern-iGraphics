#include "iGraphics.h"

Sprite bg, mario1, mario2, rect;

Sprite pinkMonster, golem;
bool isMirroredX[2] = {false, false};
#define PINK_MONSTER 0
#define GOLEM 1

void loadResources()
{
    iLoadSpriteFile(&pinkMonster, "assets\\images\\sprites\\1 Pink_Monster\\Pink_Monster_Idle_4.png", 1, 4, 0, 3, -2);
    iSetSpritePosition(&pinkMonster, 100, 100);
    iScaleSprite(&pinkMonster, 5.0);

    iLoadSpriteFolder(&golem, "assets\\images\\sprites\\Golem_2\\Walking", -2);
    iSetSpritePosition(&golem, 300, 200);
    iScaleSprite(&golem, 0.5);

    // iLoadSprite(&bg, "background.jpg", -1); // -1 for ignoring collisionMask. Whole image will be checked for collision
    // iSetSpritePosition(&bg, 200, 100);
    // iLoadSprite(&mario1, "mario.png", 0);
    // iSetSpritePosition(&mario1, 411, 204);
    // double marioAspectRatio = (double)mario1.img.width / mario1.img.height;
    // iResizeSprite(&mario1, 48, 48.0 / marioAspectRatio);

    // iLoadSprite(&mario2, "mario.png", 0);
    // iResizeSprite(&mario2, 200, 200.0 / marioAspectRatio);
    // iSetSpritePosition(&mario2, 211, 204);

    iLoadSprite(&rect, "assets\\images\\rect.png", 0xFFFFFF); // Ignore white color for collision detection
    iSetSpritePosition(&rect, -100, -50);
    iScaleSprite(&rect, 2);
    // iWrapSprite(&rect, 500);
}

void iDraw()
{
    // place your drawing codes here
    // iShowSprite(&pinkMonster);
    iShowSprite(&golem);
    // iShowSprite(&mario1);
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

void iMouseWheel(int button, int dir, int mx, int my)
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
    // iAnimateSprite(&pinkMonster, deltaTime);
    // iUpdateSprite(&mario1);
    // iUpdateSprite(&mario2);
    // iUpdateSprite(&rect);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadResources();
    iPlaySound("assets\\sounds\\background.wav", true);
    iSetTimer(50, iAnim);
    iInitialize(1920, 1057, "Sprite Demo");
    return 0;
}