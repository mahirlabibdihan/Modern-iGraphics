#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/
float degree = 0;
float degree2 = 0;
Sprite mario1, mario2;
Image marioImage;
void loadResources()
{
    iLoadImage(&marioImage, "assets/images/mario.png");
    iInitSprite(&mario1);
    iInitSprite(&mario2);
    iChangeSpriteFrames(&mario1, &marioImage, 1);
    iChangeSpriteFrames(&mario2, &marioImage, 1);
    iSetSpritePosition(&mario1, 400, 150);
    iSetSpritePosition(&mario2, 650, 100);
    iScaleSprite(&mario1, 0.2);
    iScaleSprite(&mario2, 0.4);
    iResizeImage(&marioImage, 90, 100);
}

void iDraw()
{
    // place your drawing codes here
    iClear();
    iShowLoadedImage(190, 170, &marioImage);
    iFilledCircle(200, 200, 5);
    iRotate(200, 200, degree);
    iFilledRectangle(197.5, 180, 5, 80);
    iUnRotate();

    iRotateSprite(&mario1, mario1.x + 50, mario1.y + 25, degree2);
    iShowSprite(&mario1);
    iRotateSprite(&mario2, mario2.x + 50, mario2.y + 25, degree2);
    iShowSprite(&mario2);

    if (iCheckCollision(&mario1, &mario2))
    {
        iSetColor(255, 0, 0);
        iText(0, 0, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 255, 255);
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
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case 'q':
        // do something with 'q'
        break;

    case ' ':
        degree2 += 1; // Rotate the second sprite by 5 degrees
        if (degree2 >= 360)
        {
            degree2 = 0; // Reset the rotation after a full circle
        }
    // place your codes for other keys here
    default:
        break;
    }
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

void iAnim()
{
    degree2 += 0.1;
    if (degree2 >= 360)
    {
        degree2 = 0;
    }
    degree += 2;
    if (degree >= 360)
    {
        degree = 0;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iSetTimer(10, iAnim); // Set a timer to call iAnim every 100 milliseconds
    loadResources();
    iOpenWindow(1000, 400, "demooo");
    return 0;
}
