#include "iGraphics.h"

char name[100];
char prev_names[5][100];
char *filename = "saves/names.txt";

FILE *openFile(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);
    if (file == nullptr)
    {
        printf("Failed to open file\n");
        return nullptr;
    }
    return file;
}
void closeFile(FILE *file)
{
    fclose(file);
}
void saveName()
{
    FILE *file = openFile(filename, "a");
    fprintf(file, "%s\n", name);
    closeFile(file);
}

void loadNames()
{
    FILE *file = openFile(filename, "r");
    for (int i = 0; i < 5; i++)
    {
        if (fgets(prev_names[i], 100, file) == nullptr)
        {
            break;
        }
    }
    closeFile(file);
}

void iDraw()
{
    // place your drawing codes here
    iClear();
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
    function iKeyPress() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case '\r':
        saveName();
        loadNames();
        name[0] = '\0';
        break;
    case '\b':
        if (strlen(name) > 0)
        {
            name[strlen(name) - 1] = '\0';
        }
        break;
    default:
        if (strlen(name) < 99)
        {
            name[strlen(name)] = key;
            name[strlen(name) + 1] = '\0';
        }
    }
    printf("name = %s\n", name);
}

void iSpecialKeyPress(unsigned char key)
{
    if (key == GLUT_KEY_END)
    {
        iExitMainLoop();
    }
}

int main(int argc, char *argv[])
{
    loadNames();
    iWindowedMode(600, 400, "FileDemo");
    iStartMainLoop();
    return 0;
}