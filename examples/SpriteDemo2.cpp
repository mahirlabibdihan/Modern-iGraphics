#include "iGraphics.h"
enum
{
    IDLE,
    WALK,
    JUMP
};
int pic_x, pic_y;
int idle_idx = 0;
int jump_idx = 0;
int walk_idx = 0;
int m_state = IDLE;
char monster_idle[18][100];
char monster_jump[6][100];
char monster_walk[24][100];
char *monster_image;

void populate_monster_images()
{
    for (int i = 0; i < 18; i++)
    {
        sprintf(monster_idle[i], "assets/images/sprites/Golem_2/Idle Blinking/0_Golem_Idle Blinking_%03d.png", i);
    }
    for (int i = 0; i < 6; i++)
    {
        sprintf(monster_jump[i], "assets/images/sprites/Golem_2/Jump Start/0_Golem_Jump Start_%03d.png", i);
    }
    for (int i = 0; i < 24; i++)
    {
        sprintf(monster_walk[i], "assets/images/sprites/Golem_2/Walking/0_Golem_Walking_%03d.png", i);
    }
    monster_image = monster_idle[0];
}

void update_monster()
{
    switch (m_state)
    {
    case IDLE:
        monster_image = monster_idle[idle_idx];
        idle_idx = (idle_idx + 1) % 18;
        break;
    case WALK:
        monster_image = monster_walk[walk_idx];
        walk_idx = (walk_idx + 1) % 24;
        break;
    case JUMP:
        monster_image = monster_jump[jump_idx];
        jump_idx = (jump_idx + 1) % 6;
        if (jump_idx == 0)
        {
            m_state = IDLE;
        }
        break;
    }
}
/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    iShowImage(pic_x, pic_y, monster_image);
    iShowSpeed(0, 0);
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
        pic_x -= 2;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        pic_x += 2;
        m_state = WALK;
    }
    if (key == GLUT_KEY_UP)
    {
        pic_y += 2;
        m_state = JUMP;
    }
    if (key == GLUT_KEY_DOWN)
    {
        pic_y -= 2;
    }
    // place your codes for other keys here
}

int main(int argc, char *argv[])
{
    pic_x = 0;
    pic_y = 0;
    populate_monster_images();
    iSetTimer(100, update_monster);
    iOpenWindow(900, 900, "SpriteDemo");
    return 0;
}