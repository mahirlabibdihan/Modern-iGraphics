//
//  Original Author: S. M. Shahriar Nirjon
//  last modified: May 9, 2025
//
//  Version: 2.0.2012.2015.2024.2025
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
// Include POSIX or Linux-specific headers if needed
#include <unistd.h>
#endif

#include "glut.h"
#include "freeglut_ext.h"
#include <time.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
// #include "glaux.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include "irrKlang.h"
using namespace irrklang;
using namespace std;

static int transparent = 1;
static int isFullScreen = 0;
static int old_t = -1;
typedef struct
{
    unsigned char *data;
    int width, height, channels;
} Image;

typedef struct
{
    Image image;
    int frameWidth, frameHeight;
    int columns; // Number of columns in the sheet
    int rows;    // Optional, can be derived from totalFrames / columns
} SpriteSheet;

typedef struct
{
    Image *images;
    int totalFrames;
} SpriteFrames;

typedef struct
{
    int x, y;
    SpriteSheet *sheet;
    SpriteFrames *frames;
    int startFrame;
    int currentFrame;
    int totalFrames;
    int frameDuration; // in milliseconds
    int timeSinceLastFrame;
    unsigned char *collisionMask;
    int ignoreColor;
    bool isMirroredX, isMirroredY;
    bool isSheetBased;
} Sprite;

enum MirrorState
{
    HORIZONTAL,
    VERTICAL
};

int iScreenHeight, iScreenWidth;
int iSmallScreenHeight, iSmallScreenWidth;

int iMouseX, iMouseY;
int ifft = 0;
void (*iAnimFunction[10])(void) = {0};
int iAnimCount = 0;
int iAnimDelays[10];
int iAnimPause[10];

void iDraw();
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseDrag(int, int); // Renamed from iMouseMove to iMouseDrag
void iMouseMove(int, int); // New function
void iMouse(int button, int state, int x, int y);
void iMouseWheel(int button, int dir, int x, int y);
void iResize(int width, int height);

ISoundEngine *soundEngine = createIrrKlangDevice();

#ifdef WIN32

#ifdef __x86_64
#define IMSEC unsigned long long
#else
#define IMSEC unsigned int
#endif

#endif

void timerCallback(int index)
{
    if (!iAnimPause[index] && iAnimFunction[index])
    {
        iAnimFunction[index]();
    }
    // Set the timer again to keep it repeating
    glutTimerFunc(iAnimDelays[index], timerCallback, index);
}

int iSetTimer(int msec, void (*f)(void))
{
    if (iAnimCount >= 10)
    {
        printf("Error: Maximum number of timers reached.\n");
        return -1;
    }

    int index = iAnimCount++;
    iAnimFunction[index] = f;
    iAnimDelays[index] = msec;
    iAnimPause[index] = 0;

    glutTimerFunc(msec, timerCallback, index);
    return index;
}

void iPauseTimer(int index)
{
    if (index >= 0 && index < iAnimCount)
    {
        iAnimPause[index] = 1;
    }
}

void iResumeTimer(int index)
{
    if (index >= 0 && index < iAnimCount)
    {
        iAnimPause[index] = 0;
    }
}

// Additional functions for displaying images

bool iLoadImage(Image *img, const char filename[])
{
    stbi_set_flip_vertically_on_load(true);
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (img->data == nullptr)
    {
        printf("Failed to load image: %s\n", stbi_failure_reason());
        return false;
    }
    return true;
}

void iFreeImage(Image *img)
{
    stbi_image_free(img->data);
}

void iShowImage2(int x, int y, Image *img, int ignoreColor)
{
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    if (ignoreColor != -1)
    {
        // Iterate over the pixels
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = (y * width + x) * channels;
                // Check if the pixel is the color we want to ignore
                if (data[index] == (ignoreColor & 0xFF) &&
                    data[index + 1] == ((ignoreColor >> 8) & 0xFF) &&
                    data[index + 2] == ((ignoreColor >> 16) & 0xFF))
                {
                    // Set the pixel to 0
                    data[index] = 0;
                    data[index + 1] = 0;
                    data[index + 2] = 0;
                    if (channels == 4)
                    {
                        data[index + 3] = 0;
                    }
                }
            }
        }
    }
    glRasterPos2f(x, y);
    glDrawPixels(width, height, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
}

void iShowImage(int x, int y, Image *img)
{
    iShowImage2(x, y, img, -1 /* ignoreColor */);
}

void iWrapImage(Image *img, int dx)
{
    // Right circular shift the image by dx pixels
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *wrappedData = new unsigned char[width * height * channels];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * channels;
            int wrappedX = (x + dx) % width;
            int wrappedIndex = (y * width + wrappedX) * channels;
            for (int c = 0; c < channels; c++)
            {
                wrappedData[wrappedIndex + c] = data[index + c];
            }
        }
    }
    stbi_image_free(data);
    img->data = wrappedData;
}

void iResizeImage(Image *img, int width, int height)
{
    int imgWidth = img->width;
    int imgHeight = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *resizedData = new unsigned char[width * height * channels];
    stbir_resize_uint8(data, imgWidth, imgHeight, 0, resizedData, width, height, 0, channels);
    stbi_image_free(data);
    img->data = resizedData;
    img->width = width;
    img->height = height;
}

void iScaleImage(Image *img, double scale)
{
    if (!img || scale <= 0.0f)
        return;

    int newWidth = (int)(img->width * scale);
    int newHeight = (int)(img->height * scale);
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *resizedData = new unsigned char[newWidth * newHeight * channels];

    stbir_resize_uint8(
        data, img->width, img->height, 0,
        resizedData, newWidth, newHeight, 0,
        channels);

    stbi_image_free(data);
    img->data = resizedData;
    img->width = newWidth;
    img->height = newHeight;
}

void iMirrorImage(Image *img, MirrorState state)
{
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *mirroredData = new unsigned char[width * height * channels];
    if (state == HORIZONTAL)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = (y * width + x) * channels;
                int mirroredIndex = (y * width + (width - x - 1)) * channels;
                for (int c = 0; c < channels; c++)
                {
                    mirroredData[mirroredIndex + c] = data[index + c];
                }
            }
        }
    }
    else if (state == VERTICAL)
    {
        for (int y = 0; y < height; y++)
        {
            int mirroredY = height - y - 1;
            for (int x = 0; x < width; x++)
            {
                int index = (y * width + x) * channels;
                int mirroredIndex = (mirroredY * width + x) * channels;
                for (int c = 0; c < channels; c++)
                {
                    mirroredData[mirroredIndex + c] = data[index + c];
                }
            }
        }
    }
    stbi_image_free(data);
    img->data = mirroredData;
}

// ignorecolor = hex color code 0xRRGGBB
void iUpdateCollisionMask(Sprite *s)
{
    if (s->isSheetBased)
    {
        // Use the SpriteSheet for collision mask (existing logic for SpriteSheet)
        SpriteSheet *sheet = s->sheet;
        int ignorecolor = s->ignoreColor;
        if (ignorecolor == -1)
        {
            s->collisionMask = nullptr;
            return;
        }

        int width = sheet->frameWidth;
        int height = sheet->frameHeight;
        int channels = sheet->image.channels;

        unsigned char *data = sheet->image.data;

        if (s->collisionMask != nullptr)
        {
            delete[] s->collisionMask;
        }

        unsigned char *collisionMask = new unsigned char[width * height];

        int frame = s->currentFrame;
        int col = frame % sheet->columns;
        int row = frame / sheet->columns;

        int sheetWidth = sheet->image.width;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int sheetX = col * width + x;
                int sheetY = row * height + y;
                int index = (sheetY * sheetWidth + sheetX) * channels;

                unsigned char r = data[index];
                unsigned char g = (channels > 1) ? data[index + 1] : 0;
                unsigned char b = (channels > 2) ? data[index + 2] : 0;
                unsigned char a = (channels == 4) ? data[index + 3] : 255;

                bool isTransparent = (channels == 4 && a == 0);

                bool isIgnoredColor = ignorecolor == -2 ? false : ((r == (ignorecolor & 0xFF)) && (g == ((ignorecolor >> 8) & 0xFF)) && (b == ((ignorecolor >> 16) & 0xFF)));

                collisionMask[y * width + x] = (isTransparent || isIgnoredColor) ? 0 : 1;
            }
        }
        s->collisionMask = collisionMask;
    }
    else
    {
        // Use SpriteFrames for collision mask
        if (s->frames == nullptr || s->frames->totalFrames == 0)
        {
            s->collisionMask = nullptr;
            return;
        }

        Image *frame = &s->frames->images[s->currentFrame];
        int width = frame->width;
        int height = frame->height;
        int channels = frame->channels;
        unsigned char *data = frame->data;

        int ignorecolor = s->ignoreColor;
        if (ignorecolor == -1)
        {
            s->collisionMask = nullptr;
            return;
        }

        if (s->collisionMask != nullptr)
        {
            delete[] s->collisionMask;
        }

        unsigned char *collisionMask = new unsigned char[width * height];

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = (y * width + x) * channels;

                unsigned char r = data[index];
                unsigned char g = (channels > 1) ? data[index + 1] : 0;
                unsigned char b = (channels > 2) ? data[index + 2] : 0;
                unsigned char a = (channels == 4) ? data[index + 3] : 255;

                bool isTransparent = (channels == 4 && a == 0);

                bool isIgnoredColor = ignorecolor == -2 ? false : ((r == (ignorecolor & 0xFF)) && (g == ((ignorecolor >> 8) & 0xFF)) && (b == ((ignorecolor >> 16) & 0xFF)));

                collisionMask[y * width + x] = (isTransparent || isIgnoredColor) ? 0 : 1;
            }
        }
        s->collisionMask = collisionMask;
    }
}

int iCheckCollision(Sprite *s1, Sprite *s2)
{
    SpriteSheet *sheet1 = s1->sheet;
    int width1 = sheet1->frameWidth;
    int height1 = sheet1->frameHeight;
    unsigned char *collisionMask1 = s1->collisionMask;

    SpriteSheet *sheet2 = s2->sheet;
    int width2 = sheet2->frameWidth;
    int height2 = sheet2->frameHeight;
    unsigned char *collisionMask2 = s2->collisionMask;
    int x1 = s1->x;
    int y1 = s1->y;
    int x2 = s2->x;
    int y2 = s2->y;
    // check if the two images overlap
    int startX = (x1 > x2) ? x1 : x2;
    int endX = (x1 + width1 < x2 + width2) ? x1 + width1 : x2 + width2;
    int startY = (y1 > y2) ? y1 : y2;
    int endY = (y1 + height1 < y2 + height2) ? y1 + height1 : y2 + height2;
    int noOverlap = startX >= endX || startY >= endY;
    // If collisionMasks are not set, check the whole image for collision
    if (collisionMask1 == nullptr || collisionMask2 == nullptr)
    {
        return noOverlap ? 0 : 1;
    }
    // now collisionMasks are set. Check only the overlapping region
    if (noOverlap)
    {
        return 0;
    }
    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            int index1 = (y - y1) * width1 + (x - x1);
            int index2 = (y - y2) * width2 + (x - x2);
            if (collisionMask1[index1] && collisionMask2[index2])
            {
                return 1;
            }
        }
    }
    return 0;
}

void iAnimateSprite(Sprite *sprite, float deltaTime)
{
    if (!sprite || sprite->totalFrames <= 1 || (sprite->isSheetBased && !sprite->sheet) || (!sprite->isSheetBased && !sprite->frames))
        return;

    sprite->timeSinceLastFrame += deltaTime;

    if (sprite->timeSinceLastFrame >= sprite->frameDuration)
    {
        sprite->currentFrame = (sprite->currentFrame + 1) % sprite->totalFrames;
        sprite->timeSinceLastFrame = 0.0f;

        printf("Current Frame: %d\n", sprite->currentFrame);

        // Optional: update collision mask after frame change
        iUpdateCollisionMask(sprite);
    }
}

void iLoadSpriteSheet(SpriteSheet *sheet, const char *filename, int columns, int rows)
{
    iLoadImage(&sheet->image, filename);
    sheet->columns = columns;
    sheet->rows = rows;
    sheet->frameWidth = sheet->image.width / columns;
    sheet->frameHeight = sheet->image.height / rows;
}

// Comparison function for sorting filenames
bool compareFilenames(const string &a, const string &b)
{
    return a < b;
}

void iLoadSpriteFrames(SpriteFrames *frames, const char *folderPath)
{
    printf("Loading frames from folder: %s\n", folderPath);
    DIR *dir = opendir(folderPath);
    if (dir == nullptr)
    {
        fprintf(stderr, "Failed to open directory: %s\n", folderPath);
        return;
    }
    vector<string> filenames;
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        // Skip directories
        if (entry->d_type == DT_DIR)
            continue;

        // Filter for image files (e.g., *.png, *.jpg)
        std::string filename(entry->d_name);
        // if (filename.find(".png") != std::string::npos || filename.find(".jpg") != std::string::npos || filename.find(".jpeg") != std::string::npos)
        {
            filenames.push_back(filename);
            printf("Found image: %s\n", filename.c_str());
        }
    }
    closedir(dir);
    sort(filenames.begin(), filenames.end(), compareFilenames);
    frames->totalFrames = filenames.size();
    frames->images = (Image *)malloc(sizeof(Image) * frames->totalFrames);

    // Load each image
    for (int i = 0; i < frames->totalFrames; ++i)
    {
        std::string fullPath = std::string(folderPath) + "/" + filenames[i];

        int w, h, ch;
        unsigned char *data = stbi_load(fullPath.c_str(), &w, &h, &ch, 0);
        if (!data)
        {
            fprintf(stderr, "Failed to load frame: %s\n", fullPath.c_str());
            exit(1);
        }

        frames->images[i].data = data;
        frames->images[i].width = w;
        frames->images[i].height = h;
        frames->images[i].channels = ch;
    }
}

void iLoadSprite(Sprite *s, SpriteSheet *sheet, int startFrame, int totalFrames, int frameDuration, int ignoreColor = -2)
{
    s->isSheetBased = true;
    s->sheet = sheet;
    s->x = 0;
    s->y = 0;
    s->startFrame = startFrame;
    s->currentFrame = startFrame;
    s->totalFrames = totalFrames;
    s->frameDuration = frameDuration;
    s->timeSinceLastFrame = 0.0f;
    s->collisionMask = nullptr;
    s->ignoreColor = ignoreColor;
    s->isMirroredX = false;
    s->isMirroredY = false;
    iUpdateCollisionMask(s);
}

void iLoadSprite(Sprite *s, SpriteFrames *frames, int startFrame, int totalFrames, int frameDuration, int ignoreColor = -2)
{
    s->isSheetBased = false;
    s->sheet = nullptr;
    s->startFrame = startFrame;
    s->currentFrame = startFrame;
    s->frameDuration = frameDuration; // default 100 ms per frame
    s->timeSinceLastFrame = 0;
    s->ignoreColor = ignoreColor;
    s->collisionMask = nullptr;
    s->isMirroredX = false;
    s->isMirroredY = false;
    s->frames = frames;
    s->totalFrames = totalFrames;
}

void iSetSpritePosition(Sprite *s, int x, int y)
{
    s->x = x;
    s->y = y;
}

void iShowSprite(Sprite *s)
{
    if (!s || (s->isSheetBased && (!s->sheet || !s->sheet->image.data)) || (!s->isSheetBased && !s->frames))
        return;

    if (!s->isSheetBased)
    {
        iShowImage2(s->x, s->y, &s->frames->images[s->currentFrame], s->ignoreColor);
        return;
    }

    int frame = s->currentFrame;
    int col = frame % s->sheet->columns;
    int row = frame / s->sheet->columns;

    int frameWidth = s->sheet->frameWidth;
    int frameHeight = s->sheet->frameHeight;
    int channels = s->sheet->image.channels;
    int sheetWidth = s->sheet->image.width;

    int startX = col * frameWidth;
    int startY = row * frameHeight;

    unsigned char *srcData = s->sheet->image.data;
    int ignoreColor = s->ignoreColor;

    // Temporary buffer for the frame with mirroring and ignore color applied
    unsigned char *frameBuffer = new unsigned char[frameWidth * frameHeight * channels];

    for (int y = 0; y < frameHeight; ++y)
    {
        for (int x = 0; x < frameWidth; ++x)
        {
            // Source pixel coordinates
            int srcX = startX + x;
            int srcY = startY + y;

            int srcIndex = (srcY * sheetWidth + srcX) * channels;

            unsigned char r = srcData[srcIndex];
            unsigned char g = (channels > 1) ? srcData[srcIndex + 1] : 0;
            unsigned char b = (channels > 2) ? srcData[srcIndex + 2] : 0;
            unsigned char a = (channels == 4) ? srcData[srcIndex + 3] : 255;

            bool isIgnoredColor = (ignoreColor >= 0) &&
                                  r == (ignoreColor & 0xFF) &&
                                  g == ((ignoreColor >> 8) & 0xFF) &&
                                  b == ((ignoreColor >> 16) & 0xFF);

            // Destination pixel coordinates (mirrored if needed)
            int dstX = s->isMirroredX ? (frameWidth - 1 - x) : x;
            int dstY = s->isMirroredY ? (frameHeight - 1 - y) : y;
            int dstIndex = (dstY * frameWidth + dstX) * channels;

            frameBuffer[dstIndex] = r;
            if (channels > 1)
                frameBuffer[dstIndex + 1] = g;
            if (channels > 2)
                frameBuffer[dstIndex + 2] = b;
            if (channels == 4)
                frameBuffer[dstIndex + 3] = isIgnoredColor ? 0 : a;
        }
    }

    glRasterPos2f(s->x, s->y);
    glDrawPixels(frameWidth, frameHeight, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);
    delete[] frameBuffer;
}

void iResizeSprite(Sprite *s, int width, int height)
{
    iResizeImage(&s->sheet->image, width, height);
    iUpdateCollisionMask(s);
}

void iScaleSprite(Sprite *s, double scale)
{
    if (!s || scale <= 0.0f)
        return;

    int newWidth = (int)(s->sheet->frameWidth * scale);
    int newHeight = (int)(s->sheet->frameHeight * scale);
    iScaleImage(&s->sheet->image, scale);

    s->sheet->frameWidth = newWidth;
    s->sheet->frameHeight = newHeight;

    iUpdateCollisionMask(s);
}

void iWrapSprite(Sprite *s, int dx)
{
    iWrapImage(&s->sheet->image, dx);
    iUpdateCollisionMask(s);
}

void iMirrorSprite(Sprite *s, MirrorState state)
{
    if (!s->isSheetBased)
    {
        iMirrorImage(&s->frames->images[s->currentFrame], state);
    }
    if (state == HORIZONTAL)
    {
        s->isMirroredX = !s->isMirroredX;
    }
    else if (state == VERTICAL)
    {
        s->isMirroredY = !s->isMirroredY;
    }
    iUpdateCollisionMask(s);
}

void iFreeSprite(Sprite *s)
{
    iFreeImage(&s->sheet->image);
    if (s->collisionMask != nullptr)
    {
        delete[] s->collisionMask;
    }
}

void iGetPixelColor(int cursorX, int cursorY, int rgb[])
{
    GLubyte pixel[3];
    glReadPixels(cursorX, cursorY, 1, 1,
                 GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

    rgb[0] = pixel[0];
    rgb[1] = pixel[1];
    rgb[2] = pixel[2];

    // printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
}

void iText(double x, double y, const char *str, void *font = GLUT_BITMAP_8_BY_13)
{
    glRasterPos3d(x, y, 0);
    int i;
    for (i = 0; str[i]; i++)
    {
        glutBitmapCharacter(font, str[i]); //,GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
    }
}

void iPoint(double x, double y, int size = 0)
{
    int i, j;
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    for (i = x - size; i < x + size; i++)
    {
        for (j = y - size; j < y + size; j++)
        {
            glVertex2f(i, j);
        }
    }
    glEnd();
}

void iLine(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void iFilledPolygon(double x[], double y[], int n)
{
    int i;
    if (n < 3)
        return;
    glBegin(GL_POLYGON);
    for (i = 0; i < n; i++)
    {
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}

void iPolygon(double x[], double y[], int n)
{
    int i;
    if (n < 3)
        return;
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < n; i++)
    {
        glVertex2f(x[i], y[i]);
    }
    glVertex2f(x[0], y[0]);
    glEnd();
}

void iRectangle(double left, double bottom, double dx, double dy)
{
    double x1, y1, x2, y2;

    x1 = left;
    y1 = bottom;
    x2 = x1 + dx;
    y2 = y1 + dy;

    iLine(x1, y1, x2, y1);
    iLine(x2, y1, x2, y2);
    iLine(x2, y2, x1, y2);
    iLine(x1, y2, x1, y1);
}

void iFilledRectangle(double left, double bottom, double dx, double dy)
{
    double xx[4], yy[4];
    double x1, y1, x2, y2;

    x1 = left;
    y1 = bottom;
    x2 = x1 + dx;
    y2 = y1 + dy;

    xx[0] = x1;
    yy[0] = y1;
    xx[1] = x2;
    yy[1] = y1;
    xx[2] = x2;
    yy[2] = y2;
    xx[3] = x1;
    yy[3] = y2;

    iFilledPolygon(xx, yy, 4);
}

void iFilledCircle(double x, double y, double r, int slices = 100)
{
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    xp = x + r;
    yp = y;
    glBegin(GL_POLYGON);
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + r * cos(t);
        y1 = y + r * sin(t);

        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

void iCircle(double x, double y, double r, int slices = 100)
{
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    xp = x + r;
    yp = y;
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + r * cos(t);
        y1 = y + r * sin(t);
        iLine(xp, yp, x1, y1);
        xp = x1;
        yp = y1;
    }
}

void iEllipse(double x, double y, double a, double b, int slices = 100)
{
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    xp = x + a;
    yp = y;
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        iLine(xp, yp, x1, y1);
        xp = x1;
        yp = y1;
    }
}

void iFilledEllipse(double x, double y, double a, double b, int slices = 100)
{
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    xp = x + a;
    yp = y;
    glBegin(GL_POLYGON);
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

//
// Rotates the co-ordinate system
// Parameters:
//  (x, y) - The pivot point for rotation
//  degree - degree of rotation
//
// After calling iRotate(), every subsequent rendering will
// happen in rotated fashion. To stop rotation of subsequent rendering,
// call iUnRotate(). Typical call pattern would be:
//      iRotate();
//      Render your objects, that you want rendered as rotated
//      iUnRotate();
//
void iRotate(double x, double y, double degree)
{
    // push the current matrix stack
    glPushMatrix();

    //
    // The below steps take effect in reverse order
    //

    // step 3: undo the translation
    glTranslatef(x, y, 0.0);

    // step 2: rotate the co-ordinate system across z-axis
    glRotatef(degree, 0, 0, 1.0);

    // step 1: translate the origin to (x, y)
    glTranslatef(-x, -y, 0.0);
}

void iUnRotate()
{
    glPopMatrix();
}

void iSetColor(int r, int g, int b)
{
    glColor3f(r / 255.0, g / 255.0, b / 255.0);
}

void iDelay(int sec)
{
    int t1, t2;
    t1 = time(0);
    while (1)
    {
        t2 = time(0);
        if (t2 - t1 >= sec)
            break;
    }
}

void iClear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 0);
    glFlush();
}

int iGetDeltaTime()
{
    if (old_t == -1)
    {
        old_t = glutGet(GLUT_ELAPSED_TIME);
    }
    int t = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = t - old_t;
    old_t = t;
    return deltaTime;
}
void displayFF(void)
{
    iClear();
    iDraw();
    glutSwapBuffers();
}

void animFF(void)
{
    if (ifft == 0)
    {
        ifft = 1;
        iClear();
    }
    glutPostRedisplay();
}

void keyboardHandler1FF(unsigned char key, int x, int y)
{
    iKeyboard(key);
    glutPostRedisplay();
}
void keyboardHandler2FF(int key, int x, int y)
{
    iSpecialKeyboard(key);
    glutPostRedisplay();
}

void mouseMoveHandlerFF(int mx, int my)
{
    iMouseX = mx;
    iMouseY = iScreenHeight - my;
    iMouseDrag(iMouseX, iMouseY);

    glFlush();
}

void mousePassiveMoveHandlerFF(int x, int y)
{
    iMouseX = x;
    iMouseY = iScreenHeight - y;
    iMouseMove(iMouseX, iMouseY);

    glFlush();
}

void mouseHandlerFF(int button, int state, int x, int y)
{
    iMouseX = x;
    iMouseY = iScreenHeight - y;

    iMouse(button, state, iMouseX, iMouseY);

    glFlush();
}

// Added by - Mahir Labib Dihan

void mouseWheelHandlerFF(int button, int dir, int x, int y)
{
    iMouseX = x;
    iMouseY = iScreenHeight - y;
    iMouseWheel(button, dir, iMouseX, iMouseY);

    glFlush();
}

void iPlaySound(const char *filename, bool loop) // If loop==true , then the audio will play again and again
{
    soundEngine->play2D(filename, loop); // Play an audio
}
void iStopAllSounds()
{
    soundEngine->stopAllSounds(); // Stop all sounds
}

void iSetTransparency(int state)
{
    transparent = (state == 0) ? 0 : 1;
}

void iSetLineWidth(int width = 1.0)
{
    glLineWidth(width);
}

void iToggleFullscreen()
{
    if (isFullScreen)
        glutReshapeWindow(iSmallScreenWidth, iSmallScreenHeight);
    else
        glutFullScreen();
    isFullScreen = !isFullScreen;
}

void iSetTransparentColor(int r, int g, int b, double a)
{
    glColor4f(r / 255.0, g / 255.0, b / 255.0, a);
}

void reshapeFF(int width, int height)
{
    iScreenWidth = width;
    iScreenHeight = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    iResize(width, height);
    glOrtho(0.0, iScreenWidth, 0.0, iScreenHeight, -1.0, 1.0);
    glViewport(0.0, 0.0, iScreenWidth, iScreenHeight);
    glutPostRedisplay();
}
void iInitialize(int width = 500, int height = 500, const char *title = "iGraphics")
{
    iSmallScreenHeight = iScreenHeight = height;
    iSmallScreenWidth = iScreenWidth = width;

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(title);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

    iClear();

    glutDisplayFunc(displayFF);
    glutReshapeFunc(reshapeFF);
    glutKeyboardFunc(keyboardHandler1FF); // normal
    glutSpecialFunc(keyboardHandler2FF);  // special keys
    glutMouseFunc(mouseHandlerFF);
    glutMotionFunc(mouseMoveHandlerFF);
    glutPassiveMotionFunc(mousePassiveMoveHandlerFF);
    glutMouseWheelFunc(mouseWheelHandlerFF);
    glutIdleFunc(animFF);
    //
    // Setup Alpha channel testing.
    // If alpha value is greater than 0, then those
    // pixels will be rendered. Otherwise, they would not be rendered
    //
    glAlphaFunc(GL_GREATER, 0.0f);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_LINEAR);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_LINEAR);

    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_LINEAR);

    if (transparent)
    { // added blending mode
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glutMainLoop();
    soundEngine->drop();
}
