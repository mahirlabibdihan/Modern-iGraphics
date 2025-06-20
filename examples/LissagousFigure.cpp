#include "iGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stack>
#include <time.h>
using namespace std;
#define HEIGHT 1080
#define WIDTH 1920
#define min(a, b) (a < b ? (a) : (b))
#define max(a, b) (a > b ? (a) : (b))

#define PI (acos(-1.0))
#define X1(A, T, t, O) (A * sin(2 * PI * t / T + O))
#define Y1(A, T, t, O) (A * cos(2 * PI * t / T + O))
#define X2(A, T, t, O) (A * cos(2 * PI * t / T + O))
#define Y2(A, T, t, O) (A * sin(2 * PI * t / T + O))

#define X(A, T, t, O) (A * sin(2 * PI * t / T + O))
#define Y(A, T, t, O) (A * sin(2 * PI * t / T + O))

#define YAxis 0
#define XAxis 1

double T1 = 100, A1 = 200, O1 = 0;
int Curve1 = YAxis;

double T2 = 50, A2 = 400, O2 = PI / 4;
int Curve2 = XAxis;

double t = 0;

void iDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    double i;

    iSetColor(100, 100, 100);
    iDashedLine(960, 0, 960, 1080);
    iDashedLine(0, 540, 1920, 540);

    iSetColor(191, 0, 255);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= max(T1, T2); i += .1)
    {
        double x = (Curve1 == XAxis) ? X(A1, T1, i, O1) : 0 + (Curve2 == XAxis) ? X(A2, T2, i, O2)
                                                                                : 0;
        double y = (Curve1 == YAxis) ? Y(A1, T1, i, O1) : 0 + (Curve2 == YAxis) ? Y(A2, T2, i, O2)
                                                                                : 0;
        glVertex2f(960 + x, 540 + y);
    }
    glEnd();
    double x = (Curve1 == XAxis) ? X(A1, T1, t, O1) : 0 + (Curve2 == XAxis) ? X(A2, T2, t, O2)
                                                                            : 0;
    double y = (Curve1 == YAxis) ? Y(A1, T1, t, O1) : 0 + (Curve2 == YAxis) ? Y(A2, T2, t, O2)
                                                                            : 0;
    iDashedLine(960, 540, 960 + x, 540 + y);
    iFilledCircle(960 + x, 540 + y, 15);

    // iSetColor(0,255,0);
    // glBegin(GL_LINE_STRIP);
    // for(i=0;i<=max(T1,T2);i+=.1)
    // {
    //     double x=(Curve1==XAxis)?X(A1,T1,i,O1):0+(Curve2==XAxis)?X(A2,T1,i,O2):0;
    //     double y=(Curve1==YAxis)?Y(A1,T1,i,O1):0+(Curve2==YAxis)?Y(A2,T1,i,O2):0;
    //     glVertex2f(960+x,540+y);
    // }
    // glEnd();
    // x=(Curve1==XAxis)?X(A1,T1,t,O1):0+(Curve2==XAxis)?X(A2,T1,t,O2):0;
    // y=(Curve1==YAxis)?Y(A1,T1,t,O1):0+(Curve2==YAxis)?Y(A2,T1,t,O2):0;
    // iLine(960,540,960+x,540+y);
    // iFilledCircle(960+x,540+y,15);

    t += .03;
    O2 += .0005;

    iSetTransparentColor(255, 255, 0, .5);
    // glBegin(GL_LINE_STRIP);
    // for(i=0;i<=T1;i+=.1)
    // {
    //     double x=X2(A1,T1,i,O1);
    //     double y=Y(A1,T1,i,O1);
    //     glVertex2f(960+x,540+y);
    // }
    // glEnd();
    double x1 = (Curve1 == XAxis) ? X(A1, T1, t, O1) : 0;
    double y1 = (Curve1 == YAxis) ? Y(A1, T1, t, O1) : 0;
    iLine(960, 540, 960 + x1, 540 + y1);
    iFilledCircle(960 + x1, 540 + y1, 10);
    iLine(960 + x1, 540 + y1, 960 + x, 540 + y);

    iSetTransparentColor(255, 0, 0, .5);
    // glBegin(GL_LINE_STRIP);
    // for(i=0;i<=T2;i+=.1)
    // {
    //     double x=X1(A2,T2,i,O2);
    //     double y=Y1(A2,T2,i,O2);
    //     glVertex2f(960+x,540+y);
    // }
    // glEnd();
    double x2 = (Curve2 == XAxis) ? X(A2, T2, t, O2) : 0;
    double y2 = (Curve2 == YAxis) ? Y(A2, T2, t, O2) : 0;
    iLine(960, 540, 960 + x2, 540 + y2);
    iFilledCircle(960 + x2, 540 + y2, 10);

    iLine(960 + x2, 540 + y2, 960 + x, 540 + y);
}

void iMouse(int button, int state, int mx, int my)
{
}
void iMouseDrag(int mx, int my)
{
}
void iMouseMove(int mx, int my)
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

void iKeyboard(unsigned char key)
{

    if (key == 'q')
        exit(0);
    glutPostRedisplay();
}

void iSpecialKeyboard(unsigned char key)
{
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iInitialize(1920, 1080, "Graph");
    glutFullScreen();
    glutMainLoop();
}
