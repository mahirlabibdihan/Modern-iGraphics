/***
 * iGraphics.h: v0.6.0
 * A simple graphics library for C++ using OpenGL and GLUT.
 * Provides functions for drawing shapes, images, and handling input events.
 * This library is designed to be easy to use for beginners and supports basic graphics operations.
 * It includes features like image loading, sprite handling, and collision detection.
 *
 * Author: Mahir Labib Dihan
 * Email: mahirlabibdihan@gmail.com
 * GitHub: https://github.com/mahirlabibdihan
 * Date: July 21, 2025
 */

//
//  Original Author: S. M. Shahriar Nirjon
//  Version: 2.0.2012.2015.2024.2025
//

#pragma once

#include <algorithm>
#include <cmath>
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
// Include POSIX or Linux-specific headers if needed
#include <unistd.h>
#endif

#include "freeglut.h"
#include <time.h>
#include <unordered_map>
#include <math.h>
#include <dirent.h>
#include <list>
#include <sys/stat.h>
// #include "glaux.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBIRDEF extern
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

static int transparent = 1;
static int isFullScreen = 0;
static int isGameMode = 0;
static int programEnded = 0;
const char *iWindowTitle = nullptr;
typedef struct
{
    unsigned char *data;
    int width, height, channels;
    GLuint textureId; // OpenGL texture ID
    // image type svg and non-svg
    bool isSVG = false; // true if the image is SVG, false if it's a raster image
} Image;

typedef struct
{
    Image *frames = nullptr; // Array of frames
    int count = 0;
} FrameSet;

typedef struct
{
    int x = 0, y = 0;
    FrameSet frameSet;
    int currentFrame = -1;
    unsigned char *collisionMask = nullptr;
    // int ignoreColor;
    // Tracking transformation
    float scale = 1.0f;
    bool flipHorizontal = false, flipVertical = false;
    float rotation = 0.0f;                                // in radians
    float rotationCenterX = 0.0f, rotationCenterY = 0.0f; // Center of rotation relative to the sprite's top-left corner
} Sprite;

enum MirrorState
{
    NO_MIRROR,
    HORIZONTAL,
    VERTICAL,
    MIRROR_BOTH
};

int iScreenHeight, iScreenWidth;
int iSmallScreenHeight, iSmallScreenWidth;

int iMouseX, iMouseY;
int ifft = 0;

#define MAX_TIMERS 10

void iDraw() __attribute__((weak));
void iKeyboard(unsigned char, int) __attribute__((weak)); // Deprecated: Use iKeyPress instead
void iKeyPress(unsigned char) __attribute__((weak));
void iKeyRelease(unsigned char) __attribute__((weak));
void iSpecialKeyPress(unsigned char) __attribute__((weak));
void iSpecialKeyboard(unsigned char, int) __attribute__((weak));
void iSpecialKeyRelease(unsigned char) __attribute__((weak));
void iMouse(int button, int state, int x, int y) __attribute__((weak));
void iMouseClick(int button, int state, int x, int y) __attribute__((weak));
void iMouseMove(int, int) __attribute__((weak)); // New function
void iMouseDrag(int, int) __attribute__((weak)); // Renamed from iMouseMove to iMouseDrag
void iMouseWheel(int dir, int x, int y) __attribute__((weak));
void iResize(int width, int height) __attribute__((weak));

#define mmax(a, b) ((a) > (b) ? (a) : (b))
#define mmin(a, b) ((a) < (b) ? (a) : (b))
#define sswap(a, b)           \
    do                        \
    {                         \
        typeof(a) temp = (a); \
        (a) = (b);            \
        (b) = temp;           \
    } while (0)

#ifdef WIN32

#ifdef __x86_64
#define IMSEC unsigned long long
#else
#define IMSEC unsigned int
#endif

#endif

void iInitGlut()
{
    if (!glutGet(GLUT_INIT_STATE))
    {
        int n = 1;
        char *p[1];
        p[0] = (char *)malloc(8);
        glutInit(&n, p);
    }
}

void (*iAnimFunction[MAX_TIMERS])() = {0};
void (*iAnimAdvancedFunction[MAX_TIMERS])(int) = {0};
int iAnimCount = 0;
int iAnimDelays[MAX_TIMERS];
int iAnimPause[MAX_TIMERS];
int isAdvancedTimer[MAX_TIMERS] = {0};
int iAnimLastCallTime[MAX_TIMERS] = {0};

static bool needsRedraw = false;

void markDirty() { needsRedraw = true; }

void timerCallback(int index)
{
    if (!iAnimPause[index] && (iAnimFunction[index] || iAnimAdvancedFunction[index]))
    {
        int deltaTime = 0;
        int currentTime = glutGet(GLUT_ELAPSED_TIME); // milliseconds since start
        if (iAnimLastCallTime[index] == 0)
        {
        }
        else
        {
            deltaTime = (currentTime - iAnimLastCallTime[index]); // in seconds
        }
        if (isAdvancedTimer[index])
        {
            iAnimAdvancedFunction[index](deltaTime);
        }
        else
        {
            iAnimFunction[index]();
        }
        markDirty();
        iAnimLastCallTime[index] = glutGet(GLUT_ELAPSED_TIME);
    }
    glutTimerFunc(iAnimDelays[index], timerCallback, index);
}

int iSetAdvancedTimer(int msec, void (*f)(int))
{
    iInitGlut();
    if (iAnimCount >= MAX_TIMERS)
    {
        printf("Error: Maximum number of timers reached.\n");
        return -1;
    }

    int index = iAnimCount++;
    iAnimAdvancedFunction[index] = f;
    iAnimDelays[index] = msec;
    iAnimPause[index] = 0;
    isAdvancedTimer[index] = 1;

    glutTimerFunc(msec, timerCallback, index);
    return index;
}

int iSetTimer(int msec, void (*f)())
{
    iInitGlut();
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

void iUpdateTexture(Image *img, bool resized = false)
{
    if (!img->textureId)
    {
        return; // No texture to update
    }
    glBindTexture(GL_TEXTURE_2D, img->textureId);
    GLenum format = (img->channels == 4) ? GL_RGBA : GL_RGB;

    if (resized)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format,
                     img->width, img->height, 0,
                     format, GL_UNSIGNED_BYTE, img->data);
    }
    else
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                        img->width, img->height,
                        format, GL_UNSIGNED_BYTE, img->data);
    }
}

void iIgnorePixels(Image *img, int ignoreColor = -1)
{
    if (ignoreColor == -1 || img->data == nullptr)
        return;

    unsigned char ignoreR = (ignoreColor >> 16) & 0xFF;
    unsigned char ignoreG = (ignoreColor >> 8) & 0xFF;
    unsigned char ignoreB = ignoreColor & 0xFF;

    for (int i = 0; i < img->width * img->height * img->channels; i += img->channels)
    {
        if (img->data[i] == ignoreR && img->data[i + 1] == ignoreG && img->data[i + 2] == ignoreB)
        {
            if (img->channels == 4)
            {
                img->data[i + 3] = 0; // Set alpha to 0 for transparency
            }
            else
            {
                img->data[i] = img->data[i + 1] = img->data[i + 2] = 0; // Set RGB to black
            }
        }
    }

    iUpdateTexture(img); // Update the OpenGL texture after modifying pixel data
}

bool iLoadTexture(Image *img)
{
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    // Set texture parameters ONCE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Determine format
    GLenum format = (img->channels == 4) ? GL_RGBA : GL_RGB;

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, img->width, img->height,
                 0, format, GL_UNSIGNED_BYTE, img->data);

    img->textureId = texId;
    return true;
}

bool iLoadSVG(Image *img, const char *filepath, double scale = 1.0)
{
    // Load SVG
    NSVGimage *image = nsvgParseFromFile(filepath, "px", 96.0f);
    if (!image)
    {
        fprintf(stderr, "Could not open SVG file: %s\n", filepath);
        return false;
    }

    int origW = (int)image->width;
    int origH = (int)image->height;

    int outW = (int)(origW * scale);
    int outH = (int)(origH * scale);

    // printf("SVG image size: %d x %d, scaled to: %d x %d\n", origW, origH, outW, outH);

    img->data = (unsigned char *)malloc(outW * outH * 4);
    if (!img->data)
    {
        fprintf(stderr, "Failed to allocate image buffer\n");
        nsvgDelete(image);
        return false;
    }

    NSVGrasterizer *rast = nsvgCreateRasterizer();
    if (!rast)
    {
        fprintf(stderr, "Failed to create rasterizer\n");
        free(img->data);
        nsvgDelete(image);
        return false;
    }

    nsvgRasterize(rast, image, 0, 0, scale, img->data, outW, outH, outW * 4);

    img->width = outW;
    img->height = outH;
    img->channels = 4; // RGBA
    img->isSVG = true; // Mark as SVG image
    img->textureId = 0;

    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);

    return true;
}

// Additional functions for displaying images
bool iLoadImage2(Image *img, const char filename[], int ignoreColor = -1)
{
    // Check if the image is svg based on extension
    const char *ext = strrchr(filename, '.');

    stbi_set_flip_vertically_on_load(true);
    if (ext && (strcmp(ext, ".svg") == 0 || strcmp(ext, ".SVG") == 0))
    {
        iLoadSVG(img, filename);
    }
    else
    {
        img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
        img->isSVG = false; // Mark as non-SVG image
    }

    if (img->data == nullptr)
    {
        printf("ERROR: Failed to load image: %s\n", stbi_failure_reason());
        return false;
    }

    // Ignore the pixels with the specified ignore color
    iIgnorePixels(img, ignoreColor);
    img->textureId = 0; // Initialize texture ID to 0
    return true;
}

int iLoadImage(Image *img, const char filename[])
{
    return iLoadImage2(img, filename, -1);
}

void iFreeTexture(Image *img)
{
    if (!img || img->textureId == 0)
        return;
    glDeleteTextures(1, &img->textureId);
    img->textureId = 0; // Reset texture ID after deletion
}

void iFreeImage(Image *img)
{
    iFreeTexture(img);
    if (img->data)
    {
        stbi_image_free(img->data);
        img->data = nullptr;
    }
}

void iFreeFrameSet(FrameSet *fs)
{
    if (fs->frames)
    {
        for (int i = 0; i < fs->count; ++i)
        {
            iFreeImage(&fs->frames[i]);
        }
        delete[] fs->frames;
        fs->frames = nullptr;
    }
    fs->count = 0;
}

void iLine(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
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

void iShowTexture2(int x, int y, Image *img, int width = -1, int height = -1, MirrorState mirror = NO_MIRROR)
{
    int imgWidth = width == -1 ? img->width : width;
    int imgHeight = height == -1 ? img->height : height;

    if (x + imgWidth <= 0 || y + imgHeight <= 0 || x >= iScreenWidth || y >= iScreenHeight)
        return;
    if (img->textureId == 0)
    {
        if (!iLoadTexture(img))
        {
            printf("Failed to load texture for image at (%d, %d)\n", x, y);
            return;
        }
    }

    // iRectangle(x, y, imgWidth, imgHeight); // Uncomment for debugging rectangle bounds

    glBindTexture(GL_TEXTURE_2D, img->textureId);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    float tx1 = 0.0f, ty1 = 0.0f;
    float tx2 = 1.0f, ty2 = 1.0f;

    // Handle mirror states
    if (mirror == HORIZONTAL || mirror == MIRROR_BOTH)
        sswap(tx1, tx2);
    if (mirror == VERTICAL || mirror == MIRROR_BOTH)
        sswap(ty1, ty2);

    if (img->isSVG) // If the image is an SVG, we need to flip vertically
    {
        // SVG images are typically flipped vertically in OpenGL
        sswap(ty1, ty2);
    }
    glTexCoord2f(tx1, ty1);
    glVertex2i(x, y);
    glTexCoord2f(tx2, ty1);
    glVertex2i(x + imgWidth, y);
    glTexCoord2f(tx2, ty2);
    glVertex2i(x + imgWidth, y + imgHeight);
    glTexCoord2f(tx1, ty2);
    glVertex2i(x, y + imgHeight);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// void iShowImage3(int x, int y, Image *img)
// {
//     int imgWidth = img->width;
//     int imgHeight = img->height;
//     int channels = img->channels;
//     unsigned char *data = img->data;

//     // Get OpenGL viewport size
//     GLint viewport[4];
//     glGetIntegerv(GL_VIEWPORT, viewport);
//     int screenWidth = viewport[2];
//     int screenHeight = viewport[3];

//     // Fast path: no clipping needed
//     if (x >= 0 && y >= 0)
//     {
//         glRasterPos2i(x, y);
//         glDrawPixels(imgWidth, imgHeight,
//                      (channels == 4) ? GL_RGBA : GL_RGB,
//                      GL_UNSIGNED_BYTE, data);
//         return;
//     }

//     // Improved visible region calculation with clamping
//     int startX = mmax(0, -x);
//     int startY = mmax(0, -y);
//     int drawX = mmax(0, x);
//     int drawY = mmax(0, y);

//     int drawWidth = mmin(imgWidth - startX, screenWidth - drawX);
//     int drawHeight = mmin(imgHeight - startY, screenHeight - drawY);

//     // Don't draw if completely out of bounds
//     if (drawWidth <= 0 || drawHeight <= 0)
//         return;

//     // Create a buffer for the clipped image
//     unsigned char *clippedData = new unsigned char[drawWidth * drawHeight * channels];
//     int srcStride = imgWidth * channels;
//     int dstStride = drawWidth * channels;

//     unsigned char *dstPtr = clippedData;
//     unsigned char *srcPtr = data + startY * srcStride + startX * channels;

//     for (int dy = 0; dy < drawHeight; dy++)
//     {
//         memcpy(dstPtr, srcPtr, dstStride);
//         dstPtr += dstStride;
//         srcPtr += srcStride;
//     }

//     glRasterPos2i(drawX, drawY);
//     glDrawPixels(drawWidth, drawHeight, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, clippedData);
//     delete[] clippedData;
// }

void iShowLoadedImage2(int x, int y, Image *img, int width = -1, int height = -1, MirrorState mirror = NO_MIRROR)
{
    iShowTexture2(x, y, img, width, height, mirror);
}

void iShowLoadedImage(int x, int y, Image *img)
{
    iShowLoadedImage2(x, y, img);
}

struct CacheEntry
{
    Image image;
    std::list<std::string>::iterator listIt;
};
static std::unordered_map<std::string, CacheEntry> imageCache;
static std::list<std::string> lruList; // Most recently used at front
static const size_t MAX_CACHE_SIZE = 500;

void iShowImage2(int x, int y, const char *filename, int ignoreColor = -1)
{
    std::string key = std::string(filename);

    auto it = imageCache.find(key);
    if (it != imageCache.end())
    {
        // Move to front of LRU list (most recently used)
        lruList.erase(it->second.listIt);
        lruList.push_front(key);
        it->second.listIt = lruList.begin();

        // Use cached image
        iShowTexture2(x, y, &it->second.image, -1, -1, NO_MIRROR);
        return;
    }

    Image img;
    // printf("Loading image: %s\n", filename);
    if (!iLoadImage2(&img, filename, ignoreColor))
    {
        printf("ERROR: Failed to load image: %s\n", filename);
        return;
    }

    // Add to cache (with size limit)
    if (imageCache.size() >= MAX_CACHE_SIZE)
    {
        std::string lru = lruList.back();
        lruList.pop_back();

        auto lruIt = imageCache.find(lru);
        if (lruIt != imageCache.end())
        {
            iFreeImage(&lruIt->second.image);
            imageCache.erase(lruIt);
        }
    }

    lruList.push_front(key);
    CacheEntry entry;
    entry.listIt = lruList.begin();
    entry.image = img;
    imageCache[key] = entry;

    iShowTexture2(x, y, &img, -1, -1, NO_MIRROR);
}

void iShowImage(int x, int y, const char *filename)
{
    iShowImage2(x, y, filename);
}

void iShowSVG2(double x, double y, const char *filepath, double scale = 1.0, MirrorState mirror = NO_MIRROR)
{
    // Load SVG
    Image img;
    if (!iLoadSVG(&img, filepath, scale))
    {
        printf("ERROR: Failed to load svg: %s\n", filepath);
        return;
    }
    iShowTexture2(x, y, &img, img.width, img.height, mirror);
    iFreeImage(&img);
}

void iShowSVG(double x, double y, const char *filepath)
{
    iShowSVG2(x, y, filepath);
}

void iShowLoadedSVG2(double x, double y, Image *img, MirrorState mirror = NO_MIRROR)
{
    // Ensure the image is an SVG
    if (!img->isSVG)
    {
        fprintf(stderr, "Image is not an SVG.\n");
        return;
    }

    // Load the SVG texture if not already loaded
    if (img->textureId == 0)
    {
        iLoadTexture(img);
    }

    iShowTexture2(x, y, img, img->width, img->height, mirror);
}

void iShowLoadedSVG(double x, double y, Image *img)
{
    iShowLoadedSVG2(x, y, img);
}

void iWrapImage(Image *img, int dx = 0, int dy = 0)
{
    // Circular shift the image horizontally by dx and vertically by dy pixels
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *wrappedData = new unsigned char[width * height * channels];

    // Normalize dx to [0, width), dy to [0, height)
    dx = ((dx % width) + width) % width;
    dy = ((dy % height) + height) % height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int srcIndex = (y * width + x) * channels;
            int wrappedX = (x + dx) % width;
            int wrappedY = (y + dy) % height;
            int dstIndex = (wrappedY * width + wrappedX) * channels;

            for (int c = 0; c < channels; c++)
            {
                wrappedData[dstIndex + c] = data[srcIndex + c];
            }
        }
    }

    stbi_image_free(data);
    img->data = wrappedData;

    iUpdateTexture(img);
}

void iResizeImage(Image *img, int width, int height)
{
    int imgWidth = img->width;
    int imgHeight = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;
    unsigned char *resizedData = new unsigned char[width * height * channels];
    stbir_pixel_layout layout;
    if (channels == 3)
        layout = STBIR_RGB;
    else if (channels == 4)
        layout = STBIR_RGBA;
    else
    {
        // handle error
    }
    stbir_resize_uint8_srgb(data, imgWidth, imgHeight, 0, resizedData, width, height, 0, layout);
    // stbir_resize_uint8(data, imgWidth, imgHeight, 0, resizedData, width, height, 0, channels);
    stbi_image_free(data);
    img->data = resizedData;
    img->width = width;
    img->height = height;

    iUpdateTexture(img, true); // Update OpenGL texture after resizing
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

    stbir_pixel_layout layout;
    if (channels == 3)
        layout = STBIR_RGB;
    else if (channels == 4)
        layout = STBIR_RGBA;
    else
    {
        // handle error
    }
    stbir_resize_uint8_srgb(data, img->width, img->height, 0, resizedData, newWidth, newHeight, 0, layout);
    // stbir_resize_uint8(
    //     data, img->width, img->height, 0,
    //     resizedData, newWidth, newHeight, 0,
    //     channels);

    stbi_image_free(data);
    img->data = resizedData;
    img->width = newWidth;
    img->height = newHeight;

    iUpdateTexture(img, true); // Update OpenGL texture after scaling
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

    iUpdateTexture(img); // Update OpenGL texture after mirroring
}

// ignorecolor = hex color code 0xRRGGBB
void iUpdateCollisionMask(Sprite *s)
{
    if (!s || !s->frameSet.frames)
    {
        return;
    }
    Image *frame = &s->frameSet.frames[s->currentFrame];
    int width = frame->width;
    int height = frame->height;
    int channels = frame->channels;
    unsigned char *data = frame->data;

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
            unsigned char a = (channels == 4) ? data[index + 3] : 255;
            bool isTransparent = (channels == 4 && a == 0);
            collisionMask[y * width + x] = (isTransparent) ? 0 : 1;
        }
    }
    s->collisionMask = collisionMask;
}

int iCheckImageSpriteCollision(int x1, int y1, Image *img, Sprite *s)
{
    if (!img || !s || !s->frameSet.frames || s->currentFrame < 0 || s->currentFrame >= s->frameSet.count)
        return 0; // Invalid image or sprite

    Image *frame = &s->frameSet.frames[s->currentFrame];
    int x2 = s->x;
    int y2 = s->y;

    // Calculate bounding box overlap
    int overlapMinX = mmax(x1, x2);
    int overlapMaxX = mmin(x1 + img->width, x2 + frame->width);
    int overlapMinY = mmax(y1, y2);
    int overlapMaxY = mmin(y1 + img->height, y2 + frame->height);

    if (overlapMinX >= overlapMaxX || overlapMinY >= overlapMaxY)
        return 0; // No overlap

    int count = 0;
    // Check pixel-perfect collision in the overlapping area
    for (int y = overlapMinY; y < overlapMaxY; y++)
    {
        for (int x = overlapMinX; x < overlapMaxX; x++)
        {
            // Get pixel coordinates in both images
            int localX1 = x - x1;
            int localY1 = y - y1;
            int localX2 = x - x2;
            int localY2 = y - y2;

            if (localX1 < 0 || localY1 < 0 || localX1 >= img->width || localY1 >= img->height ||
                localX2 < 0 || localY2 < 0 || localX2 >= frame->width || localY2 >= frame->height)
                continue;

            unsigned char *pixel1 = &img->data[(localY1 * img->width + localX1) * img->channels];
            unsigned char *pixel2 = &frame->data[(localY2 * frame->width + localX2) * frame->channels];

            // Check if both pixels are not transparent
            bool isPixel1Transparent = (img->channels == 4 && pixel1[3] == 0);
            bool isPixel2Transparent = (frame->channels == 4 && pixel2[3] == 0);

            if (!isPixel1Transparent && !isPixel2Transparent)
            {
                // Both pixels are opaque, collision detected
                count++;
            }
        }
    }
    return count;
}

int iCheckImageCollision(int x1, int y1, Image *img1, int x2, int y2, Image *img2)
{
    if (!img1 || !img2 || !img1->data || !img2->data)
        return 0; // Invalid images

    int w1 = img1->width, h1 = img1->height;
    int w2 = img2->width, h2 = img2->height;

    // Calculate bounding box overlap
    int overlapMinX = mmax(x1, x2);
    int overlapMaxX = mmin(x1 + w1, x2 + w2);
    int overlapMinY = mmax(y1, y2);
    int overlapMaxY = mmin(y1 + h1, y2 + h2);

    if (overlapMinX >= overlapMaxX || overlapMinY >= overlapMaxY)
        return 0; // No overlap

    int count = 0;
    // Check pixel-perfect collision in the overlapping area
    for (int y = overlapMinY; y < overlapMaxY; y++)
    {
        for (int x = overlapMinX; x < overlapMaxX; x++)
        {
            // Get pixel coordinates in both images
            int localX1 = x - x1;
            int localY1 = y - y1;
            int localX2 = x - x2;
            int localY2 = y - y2;

            if (localX1 < 0 || localY1 < 0 || localX1 >= w1 || localY1 >= h1 ||
                localX2 < 0 || localY2 < 0 || localX2 >= w2 || localY2 >= h2)
                continue;

            unsigned char *pixel1 = &img1->data[(localY1 * w1 + localX1) * img1->channels];
            unsigned char *pixel2 = &img2->data[(localY2 * w2 + localX2) * img2->channels];

            // Check if both pixels are not transparent
            bool isPixel1Transparent = (img1->channels == 4 && pixel1[3] == 0);
            bool isPixel2Transparent = (img2->channels == 4 && pixel2[3] == 0);

            if (!isPixel1Transparent && !isPixel2Transparent)
            {
                // Both pixels are opaque, collision detected
                count++;
            }
        }
    }
    return count;
}

int iCheckCollision(Sprite *s1, Sprite *s2)
{
    // Early exit if invalid sprites or missing frames/masks
    if (!s1 || !s2 || !s1->frameSet.frames || !s2->frameSet.frames || !s1->collisionMask || !s2->collisionMask)
        return 0;

    Image *frame1 = &s1->frameSet.frames[s1->currentFrame];
    Image *frame2 = &s2->frameSet.frames[s2->currentFrame];
    int w1 = frame1->width, h1 = frame1->height;
    int w2 = frame2->width, h2 = frame2->height;

    // Convert rotation angles to radians
    float theta1 = s1->rotation * (3.14159265f / 180.0f);
    float theta2 = s2->rotation * (3.14159265f / 180.0f);
    float cos1 = cosf(theta1), sin1 = sinf(theta1);
    float cos2 = cosf(theta2), sin2 = sinf(theta2);

    // Helper function to compute rotated AABB (global pivot version)
    auto computeRotatedAABB = [](float x, float y, int w, int h,
                                 float pivotX, float pivotY,
                                 float cosT, float sinT)
    {
        // Calculate local pivot offset (from sprite origin to rotation center)
        float localPivotX = pivotX - x;
        float localPivotY = pivotY - y;

        // Corners relative to sprite origin
        float cornersX[4] = {0, (float)w, 0, (float)w};
        float cornersY[4] = {0, 0, (float)h, (float)h};

        float minX = INFINITY, maxX = -INFINITY;
        float minY = INFINITY, maxY = -INFINITY;

        for (int i = 0; i < 4; i++)
        {
            // Get corner relative to pivot
            float dx = cornersX[i] - localPivotX;
            float dy = cornersY[i] - localPivotY;

            // Rotate around pivot
            float rx = x + localPivotX + (cosT * dx - sinT * dy);
            float ry = y + localPivotY + (sinT * dx + cosT * dy);

            minX = fminf(minX, rx);
            maxX = fmaxf(maxX, rx);
            minY = fminf(minY, ry);
            maxY = fmaxf(maxY, ry);
        }
        return std::make_tuple(minX, maxX, minY, maxY);
    };

    // Compute rotated bounding boxes
    float minX1, maxX1, minY1, maxY1;
    std::tie(minX1, maxX1, minY1, maxY1) =
        computeRotatedAABB(s1->x, s1->y, w1, h1,
                           s1->rotationCenterX, s1->rotationCenterY,
                           cos1, sin1);

    float minX2, maxX2, minY2, maxY2;
    std::tie(minX2, maxX2, minY2, maxY2) =
        computeRotatedAABB(s2->x, s2->y, w2, h2,
                           s2->rotationCenterX, s2->rotationCenterY,
                           cos2, sin2);

    // Find overlap area
    int overlapMinX = (int)fmaxf(minX1, minX2);
    int overlapMaxX = (int)fminf(maxX1, maxX2);
    int overlapMinY = (int)fmaxf(minY1, minY2);
    int overlapMaxY = (int)fminf(maxY1, maxY2);

    if (overlapMinX >= overlapMaxX || overlapMinY >= overlapMaxY)
        return 0; // No AABB overlap

    // printf("AABB Overlap\n");

    // Precompute inverse rotations (for screen-to-local transform)
    float invCos1 = cos1, invSin1 = -sin1; // cos(-θ) = cos(θ), sin(-θ) = -sin(θ)
    float invCos2 = cos2, invSin2 = -sin2;

    int count = 0; // Count of overlapping pixels
    // Pixel-perfect check in overlap region
    for (int y = overlapMinY; y <= overlapMaxY; y++)
    {
        for (int x = overlapMinX; x <= overlapMaxX; x++)
        {
            // Transform to Sprite 1's local space
            float dx1 = x - s1->rotationCenterX;
            float dy1 = y - s1->rotationCenterY;
            float localX1 = invCos1 * dx1 - invSin1 * dy1 + (s1->rotationCenterX - s1->x);
            float localY1 = invSin1 * dx1 + invCos1 * dy1 + (s1->rotationCenterY - s1->y);

            if (localX1 < 0 || localY1 < 0 || localX1 >= w1 || localY1 >= h1)
                continue;

            // Transform to Sprite 2's local space
            float dx2 = x - s2->rotationCenterX;
            float dy2 = y - s2->rotationCenterY;
            float localX2 = invCos2 * dx2 - invSin2 * dy2 + (s2->rotationCenterX - s2->x);
            float localY2 = invSin2 * dx2 + invCos2 * dy2 + (s2->rotationCenterY - s2->y);

            if (localX2 < 0 || localY2 < 0 || localX2 >= w2 || localY2 >= h2)
                continue;

            // Check collision masks (with nearest-neighbor sampling)
            int ix1 = (int)localX1, iy1 = (int)localY1;
            int ix2 = (int)localX2, iy2 = (int)localY2;

            if (ix1 >= 0 && iy1 >= 0 && ix1 < w1 && iy1 < h1 &&
                ix2 >= 0 && iy2 >= 0 && ix2 < w2 && iy2 < h2)
            {
                int idx1 = iy1 * w1 + ix1;
                int idx2 = iy2 * w2 + ix2;
                if (s1->collisionMask[idx1] && s2->collisionMask[idx2])
                {

                    count++;
                    // printf("Collision at pixel (%d, %d)\n", x, y);
                    // If you want to return immediately on first collision, uncomment the next line
                    // return 1;
                }
            }
        }
    }
    return count;
}

int iCheckSpriteCollision(Sprite *s1, Sprite *s2)
{
    iCheckCollision(s1, s2);
}

void iRotateSprite(Sprite *s, double x, double y, double degree)
{
    if (!s)
        return;
    s->rotation = degree;
    s->rotationCenterX = x;
    s->rotationCenterY = y;
}

// int iCheckCollision(Sprite *s1, Sprite *s2)
// {
//     if (!s1 || !s2)
//     {
//         return 0;
//     }

//     if (!s1->frames || !s2->frames)
//     {
//         return 0;
//     }

//     int width1 = s1->frames[s1->currentFrame].width;
//     int height1 = s1->frames[s1->currentFrame].height;
//     unsigned char *collisionMask1 = s1->collisionMask;

//     int width2 = s2->frames[s2->currentFrame].width;
//     int height2 = s2->frames[s2->currentFrame].height;
//     unsigned char *collisionMask2 = s2->collisionMask;

//     int x1 = s1->x;
//     int y1 = s1->y;
//     int x2 = s2->x;
//     int y2 = s2->y;
//     // check if the two images overlap
//     int startX = (x1 > x2) ? x1 : x2;
//     int endX = (x1 + width1 < x2 + width2) ? x1 + width1 : x2 + width2;
//     int startY = (y1 > y2) ? y1 : y2;
//     int endY = (y1 + height1 < y2 + height2) ? y1 + height1 : y2 + height2;
//     int noOverlap = startX >= endX || startY >= endY;

//     // If collisionMasks are not set, check the whole image for collision
//     if (collisionMask1 == nullptr || collisionMask2 == nullptr)
//     {
//         return noOverlap ? 0 : 1;
//     }
//     // now collisionMasks are set. Check only the overlapping region
//     if (noOverlap)
//     {
//         return 0;
//     }

//     for (int y = startY; y < endY; y++)
//     {
//         for (int x = startX; x < endX; x++)
//         {
//             int ix1 = x - x1;
//             int iy1 = y - y1;
//             int ix2 = x - x2;
//             int iy2 = y - y2;

//             int index1 = iy1 * width1 + ix1;
//             int index2 = iy2 * width2 + ix2;
//             if (collisionMask1[index1] && collisionMask2[index2])
//             {
//                 return 1;
//             }
//         }
//     }
//     return 0;
// }

void iAnimateSprite(Sprite *sprite)
{
    if (!sprite || sprite->frameSet.count <= 1 || !sprite->frameSet.frames)
        return;

    sprite->currentFrame = (sprite->currentFrame + 1) % sprite->frameSet.count;
    iUpdateCollisionMask(sprite);
}

// Comparison function for sorting filenames
int compareFilenames(const void *a, const void *b)
{
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    return strcmp(strA, strB);
}
void iAllocateTexture(Image *img)
{
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    // Set texture parameters ONCE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // Determine format
    GLenum format = (img->channels == 4) ? GL_RGBA : GL_RGB;
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, img->width, img->height,
                 0, format, GL_UNSIGNED_BYTE, img->data);
    img->textureId = texId;
}

int iLoadFramesFromSheet2(FrameSet *frameSet, const char *filename, int rows, int cols, int ignoreColor = -1)
{
    // Load the sprite sheet image
    Image tmp;
    iLoadImage2(&tmp, filename, ignoreColor);

    int frameWidth = tmp.width / cols;
    int frameHeight = tmp.height / rows;
    int totalFrames = cols * rows;

    // Allocate memory for the individual frames
    frameSet->frames = (Image *)malloc(sizeof(Image) * totalFrames);
    frameSet->count = totalFrames;

    // Loop to extract each frame
    for (int i = 0; i < totalFrames; ++i)
    {
        int col = i % cols;
        int row = i / cols;

        // Create an Image structure for each frame
        Image *frame = &frameSet->frames[i];
        frame->textureId = 0; // Initialize texture ID
        frame->width = frameWidth;
        frame->height = frameHeight;
        frame->channels = tmp.channels;
        frame->data = new unsigned char[frameWidth * frameHeight * frame->channels];
        frame->isSVG = false; // Assuming frames are not SVGs

        for (int y = 0; y < frameHeight; ++y)
        {
            for (int x = 0; x < frameWidth; ++x)
            {
                int srcX = col * frameWidth + x;
                int srcY = row * frameHeight + y;
                int srcIndex = (srcY * tmp.width + srcX) * tmp.channels;
                int dstIndex = (y * frameWidth + x) * frame->channels;

                for (int c = 0; c < frame->channels; ++c)
                {
                    frame->data[dstIndex + c] = tmp.data[srcIndex + c];
                }
            }
        }

        // iAllocateTexture(frame); // Set the texture ID for the frame
    }

    delete[] tmp.data;
    return totalFrames;
}

int iLoadFramesFromSheet(FrameSet *frameSet, const char *filename, int rows, int cols)
{
    return iLoadFramesFromSheet2(frameSet, filename, rows, cols);
}

#define MAX_FILES 1024
#define MAX_FILENAME_LEN 512

int iLoadFramesFromFolder2(FrameSet *frameSet, const char *folderPath, int ignoreColor = -1)
{
    DIR *dir = opendir(folderPath);
    if (dir == nullptr)
    {
        fprintf(stderr, "ERROR: Failed to open directory: %s\n", folderPath);
        return -1;
    }

    char *filenames[MAX_FILES];
    int count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && count < MAX_FILES)
    {
        const char *name = entry->d_name;

        // Skip "." and ".."
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        // Build full path to check if it's a directory
        char fullPath[MAX_FILENAME_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, name);

        struct stat st;
        if (stat(fullPath, &st) == 0 && S_ISDIR(st.st_mode))
            continue;

        // Optionally filter image files (uncomment if needed)
        filenames[count] = strdup(name);
        if (filenames[count] != NULL)
            count++;
    }
    closedir(dir);

    qsort(filenames, count, sizeof(char *), compareFilenames);

    frameSet->frames = (Image *)malloc(sizeof(Image) * count);
    frameSet->count = count;
    if (frameSet->frames == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        for (int i = 0; i < count; ++i)
            free(filenames[i]);
        return -1;
    }
    // Load images in sorted order
    for (int i = 0; i < count; ++i)
    {
        char fullPath[MAX_FILENAME_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, filenames[i]);
        iLoadImage2(&frameSet->frames[i], fullPath, ignoreColor);
        free(filenames[i]); // free allocated memory
    }
    return count; // Return the number of frames loaded
}

int iLoadFramesFromFolder(FrameSet *frameSet, const char *folderPath)
{
    return iLoadFramesFromFolder2(frameSet, folderPath);
}

void iInitSprite(Sprite *s)
{
    s->x = 0;
    s->y = 0;

    s->collisionMask = nullptr;
    // s->ignoreColor = ignoreColor;

    // Assign the pre-loaded frames to the sprite
    s->currentFrame = -1;
    s->scale = 1.0f;           // Initialize scale
    s->flipHorizontal = false; // Initialize flip state
    s->flipVertical = false;   // Initialize flip state
    s->rotation = 0.0f;        // Initialize rotation angle
    s->rotationCenterX = 0.0f; // Initialize rotation center X
    s->rotationCenterY = 0.0f; // Initialize rotation center Y
}

void deepCopyImage(Image src, Image *dst)
{
    // Copy the scalar members (width, height, channels)
    dst->width = src.width;
    dst->height = src.height;
    dst->channels = src.channels;
    dst->isSVG = src.isSVG; // Copy SVG flag
    dst->textureId = 0;     // Copy texture ID

    // Allocate memory for the image data in the destination
    dst->data = (unsigned char *)malloc(src.width * src.height * src.channels);
    if (dst->data == NULL)
    {
        // Handle memory allocation failure
        printf("ERROR: Memory allocation failed\n");
        return;
    }

    // Copy the image data byte-by-byte
    memcpy(dst->data, src.data, src.width * src.height * src.channels);
    // iAllocateTexture(dst); // Set the texture ID for the destination image
}

void iScaleSprite(Sprite *s, double scale)
{
    if (!s || scale <= 0.0f)
        return;

    s->scale *= scale;
    for (int i = 0; i < s->frameSet.count; ++i)
    {
        Image *frame = &s->frameSet.frames[i];
        iScaleImage(frame, scale);
    }

    iUpdateCollisionMask(s);
}

int iGetVisiblePixelsCount(Sprite *s)
{
    // Use sprite collision mask to count visible pixels
    if (!s || !s->collisionMask || !s->frameSet.frames)
        return 0;

    Image *frame = &s->frameSet.frames[s->currentFrame];
    int width = frame->width;
    int height = frame->height;
    int visibleCount = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            if (s->collisionMask[index] > 0) // Assuming non-zero means visible
            {
                visibleCount++;
            }
        }
    }

    return visibleCount;
}

void iChangeSpriteFrames(Sprite *s, const FrameSet *frameSet)
{
    if (s->frameSet.frames != nullptr)
    {
        iFreeFrameSet(&s->frameSet);
    }

    s->frameSet.frames = new Image[frameSet->count];
    s->frameSet.count = frameSet->count;

    for (int i = 0; i < frameSet->count; ++i)
    {
        // printf("PASSED %d\n", i);
        deepCopyImage(frameSet->frames[i], &s->frameSet.frames[i]);
    }

    s->currentFrame = 0;
    s->collisionMask = nullptr;

    // Apply transformations to each frame
    for (int i = 0; i < s->frameSet.count; ++i)
    {
        Image *frame = &s->frameSet.frames[i];
        iScaleImage(frame, s->scale);
        if (s->flipHorizontal)
            iMirrorImage(frame, HORIZONTAL);
        if (s->flipVertical)
            iMirrorImage(frame, VERTICAL);
    }
    iUpdateCollisionMask(s);
}

void iSetSpritePosition(Sprite *s, int x, int y)
{
    s->x = x;
    s->y = y;
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

void iScale(double x, double y, double scaleX, double scaleY)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(-x, -y, 0.0);
}

void iUnRotate()
{
    glPopMatrix();
}

void iUnScale()
{
    glPopMatrix();
}

void iShowSprite(const Sprite *s)
{
    if (!s || !s->frameSet.frames || s->frameSet.count == 0 || s->currentFrame < 0)
    {
        return;
    }
    iRotate(
        s->rotationCenterX,
        s->rotationCenterY,
        s->rotation);
    iShowTexture2(s->x, s->y, &s->frameSet.frames[s->currentFrame]);
    iUnRotate();
}

void iResizeSprite(Sprite *s, int width, int height)
{
    for (int i = 0; i < s->frameSet.count; ++i)
    {
        Image *frame = &s->frameSet.frames[i];
        iResizeImage(frame, width, height);
    }
    iUpdateCollisionMask(s);
}

// void iWrapSprite(Sprite *s, int dx)
// {
//     for (int i = 0; i < s->totalFrames; ++i)
//     {
//         Image *frame = &s->frames[i];
//         iWrapImage(frame, dx);
//     }
//     iUpdateCollisionMask(s);
// }

void iMirrorSprite(Sprite *s, MirrorState state)
{
    if (state == HORIZONTAL)
    {
        s->flipHorizontal = !s->flipHorizontal;
    }
    else if (state == VERTICAL)
    {
        s->flipVertical = !s->flipVertical;
    }
    for (int i = 0; i < s->frameSet.count; ++i)
    {
        Image *frame = &s->frameSet.frames[i];
        iMirrorImage(frame, state);
    }
    iUpdateCollisionMask(s);
}

void iFreeSprite(Sprite *s)
{
    if (s->frameSet.frames != nullptr)
    {
        iFreeFrameSet(&s->frameSet);
    }
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

void iStrokeText(double x, double y, const char *str, float scale = 0.1)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    for (int i = 0; str[i]; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void iSetLineWidth(float width = 1.0)
{
    glLineWidth(width);
}

float iGetLineWidth()
{
    float width;
    glGetFloatv(GL_LINE_WIDTH, &width);
    return width;
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

void iTextBold(double x, double y, const char *str, void *font = GLUT_BITMAP_8_BY_13)
{
    const double offset = 0.5;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            glRasterPos3d(x + dx * offset, y + dy * offset, 0);
            for (int i = 0; str[i]; i++)
            {
                glutBitmapCharacter(font, str[i]);
            }
        }
    }
}

void iTextAdvanced(double x, double y, const char *str, float scale = 0.3, float weight = 1.0, void *font = GLUT_STROKE_ROMAN)
{
    glPushMatrix(); // Save current transformation matrix

    glTranslatef(x, y, 0);         // Move to (x, y)
    glScalef(scale, scale, scale); // Scale down the large stroke fonts

    float width = iGetLineWidth();
    glLineWidth(weight); // Set line width for stroke font
    for (int i = 0; str[i]; i++)
    {
        glutStrokeCharacter(font, str[i]);
    }
    glLineWidth(width); // Reset line width to default
    glPopMatrix();      // Restore transformation matrix
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
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

// int iGetDeltaTime()
// {
//     if (old_t == -1)
//     {
//         old_t = glutGet(GLUT_ELAPSED_TIME);
//     }
//     int t = glutGet(GLUT_ELAPSED_TIME);
//     int deltaTime = t - old_t;
//     old_t = t;
//     return deltaTime;
// }

void displayFF(void)
{
    // iClear();
    if (iDraw)
    {
        iDraw();
        glutSwapBuffers();
    }
}

int frameCount = 0;
int previousTime = 0, previousFpsTime = 0;
int fps = 0;

void redraw()
{
    if (!programEnded || !isGameMode)
    {
        glutPostRedisplay(); // Request a redraw
    }
}

void iShowSpeed(double x, double y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    frameCount++;
    if (previousFpsTime == 0)
    {
        previousFpsTime = currentTime; // Initialize on first call
        frameCount = 0;
    }
    else
    {
        int elapsedFpsTime = currentTime - previousFpsTime;

        if (elapsedFpsTime > 1000)
        {
            fps = (frameCount * 1000.0f) / elapsedFpsTime;
            frameCount = 0;
            previousFpsTime = currentTime;
        }
    }

    char fpsText[20];
    sprintf(fpsText, "FPS: %d", fps);
    iText(x, y, fpsText);
}

void animFF(void)
{
    if (ifft == 0)
    {
        ifft = 1;
        iClear();
    }
    // if (needsRedraw)
    {
        redraw();
        needsRedraw = false;
    }
}

/* Keyboard key state. */
#define GLUT_HOLD 0x0002 // The key is being held down

bool keys[256] = {false};

int isKeyPressed(unsigned char key)
{
    return keys[key];
}

void keyboardHandler1FF(unsigned char key, int x, int y)
{
    if (iKeyPress)
    {
        if (isKeyPressed(key))
        {
            iKeyPress(key);
        }
        else
        {
            keys[key] = true;
            iKeyPress(key);
        }
    }
    else if (iKeyboard) // Deprecated
    {
        if (isKeyPressed(key))
        {
            iKeyboard(key, GLUT_HOLD); // Call with hold state
        }
        else
        {
            keys[key] = true; // Mark key as pressed
            iKeyboard(key, GLUT_DOWN);
        }
    }
    else
    {
        // printf("Warning: Keyboard functionality is not enabled.\n");
        return;
    }
    redraw();
}

void keyboardHandlerUp1FF(unsigned char key, int x, int y)
{
    if (iKeyRelease)
    {
        keys[key] = false;
        iKeyRelease(key);
        redraw();
    }
    else if (iKeyboard)
    {
        keys[key] = false;
        iKeyboard(key, GLUT_UP);
        redraw();
    }
    else
    {
        // printf("Warning: Keyboard functionality is not enabled.\n");
        return;
    }
}

bool specialKeys[256] = {false};

int isSpecialKeyPressed(int key)
{
    return specialKeys[key];
}

void keyboardHandler2FF(int key, int x, int y)
{
    if (iSpecialKeyPress)
    {
        if (isSpecialKeyPressed(key))
        {
            iSpecialKeyPress(key);
        }
        else
        {
            specialKeys[key] = true; // Mark special key as pressed
            iSpecialKeyPress(key);
        }
    }
    else if (iSpecialKeyboard) // Deprecated
    {
        if (isSpecialKeyPressed(key))
        {
            iSpecialKeyboard(key, GLUT_HOLD); // Call with hold state
        }
        else
        {
            specialKeys[key] = true; // Mark special key as pressed
            iSpecialKeyboard(key, GLUT_DOWN);
        }
    }
    else
    {
        // printf("Warning: Special keyboard functionality is not enabled.\n");
        return;
    }
    redraw();
}

void keyboardHandlerUp2FF(int key, int x, int y)
{
    if (iSpecialKeyRelease)
    {
        specialKeys[key] = false; // Mark special key as released
        iSpecialKeyRelease(key);
        redraw();
    }
    else if (iSpecialKeyboard)
    {
        specialKeys[key] = false; // Mark special key as released
        iSpecialKeyboard(key, GLUT_UP);
        redraw();
    }
    else
    {
        // printf("Warning: Special keyboard functionality is not enabled.\n");
        return;
    }
}

void mouseMoveHandlerFF(int mx, int my)
{
    if (!iMouseDrag)
    {
        // printf("Warning: Mouse drag functionality is not enabled.\n");
        return;
    }

    iMouseX = mx;
    iMouseY = iScreenHeight - my;
    iMouseDrag(iMouseX, iMouseY);
    redraw();
}

void mousePassiveMoveHandlerFF(int x, int y)
{
    if (!iMouseMove)
    {
        // printf("Warning: Mouse move functionality is not enabled.\n");
        return;
    }
    iMouseX = x;
    iMouseY = iScreenHeight - y;
    iMouseMove(iMouseX, iMouseY);
    redraw();
}

void mouseHandlerFF(int button, int state, int x, int y)
{
    if (iMouseClick)
    {
        iMouseX = x;
        iMouseY = iScreenHeight - y;
        iMouseClick(button, state, iMouseX, iMouseY);
    }
    else if (iMouse)
    {
        iMouseX = x;
        iMouseY = iScreenHeight - y;
        iMouse(button, state, iMouseX, iMouseY);
    }
    else
    {
        // printf("Warning: Mouse functionality is not enabled.\n");
        return;
    }
    redraw();
}

void mouseWheelHandlerFF(int button, int dir, int x, int y)
{
    if (!iMouseWheel)
    {
        // printf("Warning: Mouse wheel functionality is not enabled.\n");
        return;
    }

    iMouseX = x;
    iMouseY = iScreenHeight - y;
    iMouseWheel(dir, iMouseX, iMouseY);
    redraw();
}

void iSetTransparency(int state)
{
    transparent = (state == 0) ? 0 : 1;
}

void iToggleFullscreen()
{
    if (!isGameMode)
    {
        if (isFullScreen)
            // glutReshapeWindow(iSmallScreenWidth, iSmallScreenHeight);
            glutLeaveFullScreen();
        else
            glutFullScreen();
        isFullScreen = !isFullScreen;
    }
}

void iEnterFullscreen()
{
    if (isGameMode)
    {
        printf("Warning: Cannot toggle fullscreen in game mode.\n");
        return;
    }

    if (!isFullScreen)
    {
        glutFullScreen();
        isFullScreen = 1;
        // printf("Entered fullscreen mode.\n");
    }
    else
    {
        // printf("Warning: Already in fullscreen mode.\n");
    }
}

void iLeaveFullscreen()
{
    if (isGameMode)
    {
        printf("Warning: Cannot toggle fullscreen in game mode.\n");
        return;
    }

    if (isFullScreen)
    {
        glutLeaveFullScreen();
        isFullScreen = 0;
        // printf("Left fullscreen mode.\n");
    }
    else
    {
        // printf("Already in windowed mode.\n");
    }
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

    if (iResize)
    {
        iResize(width, height); // Need to define iResize in main file
    }
    else
    {
        // printf("Note: You can control what happens on window resize.\n");
    }
    glOrtho(0.0, iScreenWidth, 0.0, iScreenHeight, -1.0, 1.0);
    glViewport(0.0, 0.0, iScreenWidth, iScreenHeight);
    redraw();

    // glutReshapeWindow(iSmallScreenWidth, iSmallScreenHeight); // Comment above lines and uncomment this line to disable window resizing. (Credit: Mohammad Kamrul Hasan)
}

void iHideCursor()
{
    glutSetCursor(GLUT_CURSOR_NONE);
}

void iShowCursor()
{
    glutSetCursor(GLUT_CURSOR_INHERIT);
}

void iInit()
{

    // Basic OpenGL setup
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Set up viewport and orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, iScreenWidth, 0.0, iScreenHeight, -1.0, 1.0);

    iClear();

    // Register callbacks
    glutDisplayFunc(displayFF);
    glutReshapeFunc(reshapeFF);
    glutKeyboardFunc(keyboardHandler1FF);     // normal
    glutKeyboardUpFunc(keyboardHandlerUp1FF); // normal up
    glutSpecialFunc(keyboardHandler2FF);      // special keys
    glutSpecialUpFunc(keyboardHandlerUp2FF);  // special keys up
    glutMouseFunc(mouseHandlerFF);
    glutMotionFunc(mouseMoveHandlerFF);
    glutPassiveMotionFunc(mousePassiveMoveHandlerFF);
    glutMouseWheelFunc(mouseWheelHandlerFF);
    glutIdleFunc(animFF);

    // Enable alpha testing
    glAlphaFunc(GL_GREATER, 0.0f);
    glEnable(GL_ALPHA_TEST);

    // Enable smoothing
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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // critical

    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}

void iExitMainLoop()
{
    if (isGameMode)
    {
        // glutLeaveGameMode();
        glutLeaveMainLoop();
    }
    else
    {
        glutLeaveMainLoop();
    }
    programEnded = 1;
}

void iCloseWindow()
{
    if (isGameMode)
    {
        // glutLeaveGameMode();
        glutLeaveMainLoop();
    }
    else
    {
        glutLeaveMainLoop();
    }
    programEnded = 1;
}

#define W649_X_H480 "640x480"
#define W800_X_H600 "800x600"
#define W1024_X_H768 "1024x768"
#define W1280_X_H720 "1280x720"
#define W1366_X_H768 "1366x768"

void iWindowedMode(int width = 500, int height = 500, const char *title = "iGraphics")
{
    iInitGlut();

    iSmallScreenHeight = iScreenHeight = height;
    iSmallScreenWidth = iScreenWidth = width;
    iWindowTitle = title;

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);

    glutInitWindowSize(iScreenWidth, iScreenHeight);
    glutInitWindowPosition(10, 10);

    glutCreateWindow(title);

    isGameMode = 0; // Not in game mode
    iInit();
}

void iGameMode(const char *gameModeStr = W800_X_H600)
{
    // Ensure GLUT was initialized
    iInitGlut();

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);

    if (isGameMode)
    {
        printf("ERROR: Game Mode already active.\n");
        return;
    }

    // Set the game mode string
    glutGameModeString(gameModeStr);
    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
    {
        glutEnterGameMode();
        isGameMode = 1;
    }
    else
    {
        printf("ERROR: Game Mode not possible with %s\n", gameModeStr);
        return; // Game mode not possible
    }

    iInit();
    // glutMainLoop();
}
void iStartMainLoop()
{
    glutMainLoop();
}
void iOpenWindow(int width = 500, int height = 500, const char *title = "iGraphics", int fullscreen = 0)
{
    // Ensure GLUT was initialized
    iInitGlut();

    iSmallScreenHeight = iScreenHeight = height;
    iSmallScreenWidth = iScreenWidth = width;
    iWindowTitle = title;

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);

    if (fullscreen)
    {
        char gameModeStr[20];
        sprintf(gameModeStr, "%dx%d", width, height);
        glutGameModeString(gameModeStr); // Supports: 640×480 800×600 1024×768 1280×720 1366x768
        if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
        {
            isFullScreen = 1;
            glutEnterGameMode();
        }
        else
        {
            printf("ERROR: Game Mode not possible with %s\n", gameModeStr);
            // Fallback to normal window
            glutInitWindowSize(iScreenWidth, iScreenHeight);
            glutInitWindowPosition(10, 10);

            glutCreateWindow(title);
        }
    }
    else
    {
        glutInitWindowSize(iScreenWidth, iScreenHeight);
        glutInitWindowPosition(10, 10);

        glutCreateWindow(title);
    }
    iInit();
    glutMainLoop();
}

void iInitialize(int width = 500, int height = 500, const char *title = "iGraphics")
{
    iOpenWindow(width, height, title, 0);
}