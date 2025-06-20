/*
    Author: Saifur Rahman, CSE, BUET
    Last modified: July 17, 2019
*/
#include "iGraphics.h"
#include "GL/gl.h"

#define DEL_SCREEN_X 5
#define DEL_SCREEN_Y 5

#define PLANET_ORBIT_TOGGLER 'o'
#define PLANET_ORBIT_TOGGLER_CAPS 'O'
#define SATELLITE_ORBIT_TOGGLER 's'
#define SATELLITE_ORBIT_TOGGLER_CAPS 'S'

int g_sunX, g_sunY, g_sunR;
int g_fDrawPlanetOrbit = 1;
int g_fDrawSatelliteOrbit = 1;
double g_scaleFactor = 1;

typedef struct _Planet
{
    int majorAxisLen;
    int minorAxisLen;
    int radius;
    int sweepAngle;
    int delSweepAngle;
    struct
    {
        int r, g, b;
    } rgb;
    _Planet *satellites;
} Planet;

Planet g_satellite[] = {
    {50, 35, 5, 0, 10, {125, 50, 50}, NULL},
};

Planet g_planet[] = {
    {320, 240, 6, 0, 5, {256, 50, 50}, NULL},
    {400, 300, 11, 0, 2, {200, 80, 80}, NULL},
    {500, 360, 10, 0, 1, {125, 125, 125}, &g_satellite[0]},
    {1200, 300, 6, 0, 10, {0, 256, 0}, NULL},
    {1000, 400, 5, 0, 10, {256, 0, 0}, NULL}};
#define N_PLANETS (sizeof(g_planet) / sizeof(g_planet[0]))

int g_satelliteOrbitR, g_satelliteR, g_satelliteSweepAngle;

void drawStar(int x, int y, int r)
{
    iSetColor(255, 255, 0);
    iFilledCircle(x * g_scaleFactor, y * g_scaleFactor, r * g_scaleFactor);
}

void drawPlanet(int x, int y, Planet planet, int fDrawOrbit, int fDrawSatOrbit)
{
    Planet *pSat = planet.satellites;
    ;
    double pi = 2 * acos(0);
    double sweepRadian = planet.sweepAngle * pi / 180;
    int planetX = x + planet.majorAxisLen * cos(sweepRadian);
    int planetY = y + planet.minorAxisLen * sin(sweepRadian);

    if (fDrawOrbit)
    {
        iSetColor(255, 255, 255);
        iEllipse(x * g_scaleFactor, y * g_scaleFactor, planet.majorAxisLen * g_scaleFactor, planet.minorAxisLen * g_scaleFactor);
    }

    iSetColor(planet.rgb.r, planet.rgb.g, planet.rgb.b);
    iFilledCircle(planetX * g_scaleFactor, planetY * g_scaleFactor, planet.radius * g_scaleFactor);

    // Now draw the satellites
    while (pSat)
    {
        double satelliteSweepRadian = pSat->sweepAngle * pi / 180;
        int centerX = planetX + sqrt(pow(pSat->majorAxisLen, 2) - pow(pSat->minorAxisLen, 2));
        int centerY = planetY;
        int satelliteX = centerX + pSat->majorAxisLen * cos(satelliteSweepRadian);
        int satelliteY = centerY + pSat->minorAxisLen * sin(satelliteSweepRadian);
        int satelliteR = pSat->radius;

        if (fDrawSatOrbit)
        {
            iSetColor(255, 255, 255);
            iEllipse(centerX * g_scaleFactor, centerY * g_scaleFactor, pSat->majorAxisLen * g_scaleFactor, pSat->minorAxisLen * g_scaleFactor);
        }

        iSetColor(pSat->rgb.r, pSat->rgb.g, pSat->rgb.b);
        iFilledCircle(satelliteX * g_scaleFactor, satelliteY * g_scaleFactor, satelliteR * g_scaleFactor);
        pSat = pSat->satellites;
    }
}

void drawSatellite(
    int x,
    int y,
    int planetOrbitA,
    int planetOrbitB,
    int planetSweepAngle,
    int satelliteOrbitR,
    int satelliteR,
    int satelliteSweepAngle)
{
    double pi = 2 * acos(0);
    double planetSweepRadian = planetSweepAngle * pi / 180;
    double satelliteSweepRadian = satelliteSweepAngle * pi / 180 + planetSweepRadian;

    int planetX = x + planetOrbitA * cos(planetSweepRadian);
    int planetY = y + planetOrbitB * sin(planetSweepRadian);

    int satelliteX = planetX + satelliteOrbitR * cos(satelliteSweepRadian);
    int satelliteY = planetY + satelliteOrbitR * sin(satelliteSweepRadian);

    iSetColor(62, 62, 62);
    iFilledCircle(satelliteX, satelliteY, satelliteR);
}

/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{
    double centerX, centerY;
    int i;

    iClear();

    //
    // The sun is at the left focal point of the eliptical orbit. So, the center of orbit
    // needs to be translated appropriately.
    //
    drawStar(g_sunX, g_sunY, g_sunR);

    for (i = 0; i < N_PLANETS; i++)
    {
        centerX = g_sunX + sqrt(pow(g_planet[i].majorAxisLen, 2) - pow(g_planet[i].minorAxisLen, 2));
        centerY = g_sunY;
        drawPlanet(centerX, centerY, g_planet[i], g_fDrawPlanetOrbit, g_fDrawSatelliteOrbit);
    }
    iSetColor(255, 255, 255);
    iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
    function iMouseMove() is called when the user presses and drags the mouse.
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
void iMouseWheel(int dir, int mx, int my)
{
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
    switch (key)
    {
    case 'p':
    case 'P':
        iPauseTimer(0);
        break;
    case 'r':
    case 'R':
        iResumeTimer(0);
        break;

    case PLANET_ORBIT_TOGGLER:
    case PLANET_ORBIT_TOGGLER_CAPS:
        g_fDrawPlanetOrbit = !g_fDrawPlanetOrbit;
        break;

    case SATELLITE_ORBIT_TOGGLER:
    case SATELLITE_ORBIT_TOGGLER_CAPS:
        g_fDrawSatelliteOrbit = !g_fDrawSatelliteOrbit;
        break;
    }
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
    switch (key)
    {

    case GLUT_KEY_LEFT:
        g_sunX += DEL_SCREEN_X;
        break;
    case GLUT_KEY_RIGHT:
        g_sunX -= DEL_SCREEN_X;
        break;
    case GLUT_KEY_DOWN:
        g_sunY += DEL_SCREEN_Y;
        break;
    case GLUT_KEY_UP:
        g_sunY -= DEL_SCREEN_Y;
        break;
    case GLUT_KEY_PAGE_UP:
        g_scaleFactor *= 1.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        g_scaleFactor /= 1.2;
        break;

    case GLUT_KEY_END:
        exit(0);
    }
}

void movePlanets()
{
    int i;

    for (i = 0; i < N_PLANETS; i++)
    {
        g_planet[i].sweepAngle = (g_planet[i].sweepAngle + g_planet[i].delSweepAngle) % 360;
        Planet *pSat = g_planet[i].satellites;
        while (pSat)
        {
            pSat->sweepAngle = (pSat->sweepAngle + pSat->delSweepAngle) % 360;
            pSat = pSat->satellites;
        }
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    const int CX_MAX = 1366;
    const int CY_MAX = 768;

    // Initialize Sun's position and size.
    g_sunX = 150;
    g_sunY = CY_MAX / 2;
    g_sunR = 40;

    // Initialize moon's orbit and radius
    g_satelliteOrbitR = 20;
    g_satelliteR = 5;

        iSetTimer(20, movePlanets);
    iInitialize(CX_MAX, CY_MAX, "Solar system!");

    return 0;
}
