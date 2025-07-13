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

void iDashedLine(double x1, double y1, double x2, double y2)
{

    int j;

    double dir = (atan(abs(1.0 * (y1 - y2) / (x1 - x2))) * 180) / acos(-1);

    if (dir > 45)
    {
        double m = 1.0 * (x1 - x2) / (y1 - y2);
        double c = x1 - y1 * m;
        for (j = min(y1, y2); j <= max(y1, y2) - 15; j += 30)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(m * j + c, j);
            glVertex2f(m * (j + 15) + c, j + 15);
            glEnd();
        }
    }
    else
    {
        double m = 1.0 * (y1 - y2) / (x1 - x2);
        double c = y1 - x1 * m;
        for (j = min(x1, x2); j <= max(x1, x2) - 15; j += 30)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(j, m * j + c);
            glVertex2f(j + 15, m * (j + 15) + c);
            glEnd();
        }
    }
}

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

void iKeyPress(unsigned char key)
{
    if (key == 'q')
        exit(0);
}

int main(int argc, char *argv[])
{
    iOpenWindow(1920, 1080, "Graph");
    return 0;
}