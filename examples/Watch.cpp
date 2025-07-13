#include "iGraphics.h"
#include <math.h>
#include <time.h>

double o, x = 500, y = 360 + 250, sx, sy, p;
double xm = 500, ym = 360 + 220, mx, my, pm;
double xh = 500, yh = 360 + 200, hx, hy, ph, H, M, S;
int i;

void iDraw()
{

    iClear();

    iSetColor(10, 10, 10);
    iFilledCircle(500, 360, 300); // Large

    iSetColor(0, 255, 0);
    iCircle(500, 360, 305); // out
    iSetColor(0, 0, 255);
    iCircle(500, 360, 275); // nextout
    iSetColor(255, 0, 0);
    for (i = 1, o = (6 / 57.29); i <= 60; i++, o += (6 / 57.29))
    {
        if (i % 5 != 0)
            iFilledCircle(500 + 295 * cos(o), 360 + 295 * sin(o), 4);
        if (i % 5 == 0)
            iFilledCircle(0, 0, 0);
    }

    iSetColor(255, 0, 0);
    iLine(500, 360, x, y); /// second
    iSetColor(0, 120, 120);
    iLine(500, 360, xm, ym); /// minit
    iSetColor(20, 200, 40);
    iLine(500, 360, xh, yh); // HR
    iSetColor(255, 0, 0);
    iText(500 + 244, 360 - 150, "IV");   // 4(500+259,360-150)point
    iText(500 + 145, 360 - 256, "V");    //	iFilledCircle(500+150,360-260,5);//60
    iText(495, 60, "VI");                // iFilledCircle(500,65,5);//lower
    iText(500 - 155, 360 - 257, "VII");  // iFilledCircle(500-150,360-260,5);//120
    iText(200, 360, "IX");               // iFilledCircle(205,360,5);//left
    iText(500 - 255, 360 + 145, "X");    // iFilledCircle(500-260,360+150,5);//150
    iText(500 + 240, 360 + 150, "II");   // iFilledCircle(500+259,360+150,5);//330
    iText(500 + 140, 360 + 252, "I");    //	iFilledCircle(500+150,360+260,5);//300
    iText(490, 650, "XII");              //	iFilledCircle(500,655,5);//upper
    iText(777, 360, "III");              //	iFilledCircle(795,360,5);//right
    iText(500 - 150, 360 + 250, "XI");   //	iFilledCircle(500-150,360+260,5);//240
    iText(500 - 260, 360 - 150, "VIII"); //	iFilledCircle(500-260,360-150,5);//210
    iSetColor(20, 50, 210);
    iFilledCircle(500, 360, 20); // small
}

void second()
{
    sx = 250 * cos(p / 57.29);
    sy = 250 * sin(p / 57.29);
    x = 500 + sx;
    y = 360 + sy;
    p = p - 6;
}
void minute()
{
    mx = 220 * cos(pm / 57.29);
    my = 220 * sin(pm / 57.29);
    xm = 500 + mx;
    ym = 360 + my;
    pm = pm - .1;
}
void hour()
{
    hx = 200 * cos(ph / 57.29);
    hy = 200 * sin(ph / 57.29);
    xh = 500 + hx;
    yh = 360 + hy;
    ph = ph - 1 / 600;
}

int main(int argc, char *argv[])
{
    time_t rawtime;
    tm *ptm;

    time(&rawtime);

    ptm = gmtime(&rawtime); // getting time from bios

    H = (ptm->tm_hour + 6) % 24;
    M = ptm->tm_min;
    S = (ptm->tm_sec) + 2;

    ph = (3 - H) * 30.0 - 30 * M / 60.0 - 30 * S / 3600.0 + .1 / 600 + 270 + 90;

    pm = (15 - M) * 6.0 - S / 60.0 + .1 + 270 + 90;

    p = (15 - S) * 6.0 + 6 + 270 + 90;

    second();
    minute();
    hour();

    iSetTimer(1000, second);
    iSetTimer(1000, minute);
    iSetTimer(1000, hour);
    iOpenWindow(1000, 720, "demo");
    return 0;
}