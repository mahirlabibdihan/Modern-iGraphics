#include "iGraphics.h"

char name[100];
char prev_names[5][100];
char *filename = "saves/names.txt";

void saveName()
{
    FILE *file = fopen(filename, "a");
    if (file == nullptr)
    {
        printf("Failed to open file\n");
        return;
    }
    fprintf(file, "%s\n", name);
    fclose(file);
}

void loadNames()
{
    FILE *file = fopen(filename, "r");
    if (file == nullptr)
    {
        printf("Failed to open file\n");
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        if (fgets(prev_names[i], 100, file) == nullptr)
        {
            break;
        }
    }
    fclose(file);
}

void iDraw()
{
    // place your drawing codes here
    iClear();
    // iText(10, 10, "Move the mouse cursor to see real-time coordinates", GLUT_BITMAP_HELVETICA_12);
    // textbox to take input
    iText(50, 50, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
    iRectangle(190, 40, 200, 30);
    if (strlen(name) > 0)
    {
        iText(192, 48, name, GLUT_BITMAP_HELVETICA_18);
    }
    // previous names
    iText(50, 100, "Previous names: ", GLUT_BITMAP_HELVETICA_18);
    for (int i = 0; i < 5; i++)
    {
        iText(50, 120 + 20 * i, prev_names[i], GLUT_BITMAP_HELVETICA_18);
    }
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
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
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
    if (key == '\r')
    {
        saveName();
        loadNames();
        name[0] = '\0';
    }
    else if (key == '\b')
    {
        if (strlen(name) > 0)
        {
            name[strlen(name) - 1] = '\0';
        }
    }
    else
    {
        if (strlen(name) < 99)
        {
            name[strlen(name)] = key;
            name[strlen(name) + 1] = '\0';
        }
    }
    printf("name = %s\n", name);
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

    // place your codes for other keys here
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    loadNames();
    iInitialize(600, 400, "Mousedemo");
    return 0;
}