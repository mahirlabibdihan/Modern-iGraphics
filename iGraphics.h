//
//  Original Author: S. M. Shahriar Nirjon
//  last modified: May 16, 2025 (Mahir Labib Dihan)
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
#include <dirent.h>
#include <sys/stat.h>
// #include "glaux.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
using namespace std;

static int transparent = 1;
static int isFullScreen = 0;
typedef struct
{
    unsigned char *data;
    int width, height, channels;
    GLuint textureId; // OpenGL texture ID
} Image;

typedef struct
{
    int x, y;
    Image *frames; // Array of individual frame images
    int currentFrame;
    int totalFrames;
    unsigned char *collisionMask;
    // int ignoreColor;

    // Tracking transformation
    float scale;
    bool flipHorizontal, flipVertical;
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

void (*iAnimFunction[MAX_TIMERS])(void) = {0};
int iAnimCount = 0;
int iAnimDelays[MAX_TIMERS];
int iAnimPause[MAX_TIMERS];

void iDraw();
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseDrag(int, int); // Renamed from iMouseMove to iMouseDrag
void iMouseMove(int, int); // New function
void iMouse(int button, int state, int x, int y);
void iMouseWheel(int dir, int x, int y);
// void iResize(int width, int height);

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define swap(a, b)            \
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

void timerCallback(int index)
{
    if (!iAnimPause[index] && iAnimFunction[index])
    {
        // int currentTime = glutGet(GLUT_ELAPSED_TIME);             // milliseconds since start
        // int deltaTime = (currentTime - iAnimLastCallTime[index]); // in seconds
        // iAnimLastCallTime[index] = currentTime;
        iAnimFunction[index]();
    }

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

// Additional functions for displaying images
bool iLoadImage(Image *img, const char filename[], int ignoreColor = -1)
{
    stbi_set_flip_vertically_on_load(true);
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (img->data == nullptr)
    {
        printf("Failed to load image: %s\n", stbi_failure_reason());
        return false;
    }

    // Ignore the pixels with the specified ignore color
    iIgnorePixels(img, ignoreColor);
    img->textureId = 0; // Initialize texture ID to 0
    return true;
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
    stbi_image_free(img->data);
}

void iShowTexture2(int x, int y, Image *img, double scaleX = 1.0, double scaleY = 1.0, MirrorState mirror = NO_MIRROR)
{
    int imgWidth = img->width * scaleX;
    int imgHeight = img->height * scaleY;

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

    glBindTexture(GL_TEXTURE_2D, img->textureId);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    float tx1 = 0.0f, ty1 = 0.0f;
    float tx2 = 1.0f, ty2 = 1.0f;

    // Handle mirror states
    if (mirror == HORIZONTAL || mirror == MIRROR_BOTH)
        swap(tx1, tx2);
    if (mirror == VERTICAL || mirror == MIRROR_BOTH)
        swap(ty1, ty2);

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

void iShowTexture(int x, int y, const char *filename, double scaleX = 1.0, double scaleY = 1.0, MirrorState mirror = NO_MIRROR, int ignoreColor = -1)
{
    Image img;
    if (!iLoadImage(&img, filename, ignoreColor))
    {
        return;
    }

    iShowTexture2(x, y, &img, scaleX, scaleY, mirror);
    iFreeImage(&img);
}

void iShowImage2(int x, int y, Image *img)
{
    int imgWidth = img->width;
    int imgHeight = img->height;
    int channels = img->channels;
    unsigned char *data = img->data;

    // Get OpenGL viewport size
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int screenWidth = viewport[2];
    int screenHeight = viewport[3];

    // Fast path: no clipping needed
    if (x >= 0 && y >= 0)
    {
        glRasterPos2i(x, y);
        glDrawPixels(imgWidth, imgHeight,
                     (channels == 4) ? GL_RGBA : GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        return;
    }

    // Improved visible region calculation with clamping
    int startX = max(0, -x);
    int startY = max(0, -y);
    int drawX = max(0, x);
    int drawY = max(0, y);

    int drawWidth = min(imgWidth - startX, screenWidth - drawX);
    int drawHeight = min(imgHeight - startY, screenHeight - drawY);

    // Don't draw if completely out of bounds
    if (drawWidth <= 0 || drawHeight <= 0)
        return;

    // Create a buffer for the clipped image
    unsigned char *clippedData = new unsigned char[drawWidth * drawHeight * channels];
    int srcStride = imgWidth * channels;
    int dstStride = drawWidth * channels;

    unsigned char *dstPtr = clippedData;
    unsigned char *srcPtr = data + startY * srcStride + startX * channels;

    for (int dy = 0; dy < drawHeight; dy++)
    {
        memcpy(dstPtr, srcPtr, dstStride);
        dstPtr += dstStride;
        srcPtr += srcStride;
    }

    glRasterPos2i(drawX, drawY);
    glDrawPixels(drawWidth, drawHeight, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, clippedData);
    delete[] clippedData;
}

void iShowLoadedTexture(int x, int y, Image *img, double scaleX = 1.0, double scaleY = 1.0, MirrorState mirror = NO_MIRROR)
{
    iShowTexture2(x, y, img, scaleX, scaleY, mirror);
}

void iShowLoadedImage(int x, int y, Image *img, double scaleX = 1.0, double scaleY = 1.0, MirrorState mirror = NO_MIRROR)
{
    iShowTexture2(x, y, img, scaleX, scaleY, mirror);
}

void iShowImage(int x, int y, const char *filename, double scaleX = 1.0, double scaleY = 1.0, MirrorState mirror = NO_MIRROR, int ignoreColor = -1)
{
    Image img;
    if (!iLoadImage(&img, filename, ignoreColor))
    {
        printf("Failed to load image: %s\n", filename);
        return;
    }
    iShowTexture2(x, y, &img, scaleX, scaleY, mirror);
    iFreeImage(&img);
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
    stbir_resize_uint8(data, imgWidth, imgHeight, 0, resizedData, width, height, 0, channels);
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

    stbir_resize_uint8(
        data, img->width, img->height, 0,
        resizedData, newWidth, newHeight, 0,
        channels);

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
    if (!s || !s->frames)
    {
        return;
    }
    // int ignorecolor = s->ignoreColor;
    // if (ignorecolor == -1)
    // {
    //     s->collisionMask = nullptr;
    //     return;
    // }

    Image *frame = &s->frames[s->currentFrame];
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

            // unsigned char r = data[index];
            // unsigned char g = (channels > 1) ? data[index + 1] : 0;
            // unsigned char b = (channels > 2) ? data[index + 2] : 0;
            unsigned char a = (channels == 4) ? data[index + 3] : 255;

            bool isTransparent = (channels == 4 && a == 0);

            // bool isIgnoredColor = (ignorecolor == -1 ? false : ((r == (ignorecolor >> 16 & 0xFF)) && (g == ((ignorecolor >> 8) & 0xFF)) && (b == ((ignorecolor) & 0xFF))));

            collisionMask[y * width + x] = (isTransparent) ? 0 : 1;
        }
    }
    s->collisionMask = collisionMask;
}

int iCheckCollision(Sprite *s1, Sprite *s2)
{
    if (!s1 || !s2)
    {
        return 0;
    }

    if (!s1->frames || !s2->frames)
    {
        return 0;
    }

    int width1 = s1->frames[s1->currentFrame].width;
    int height1 = s1->frames[s1->currentFrame].height;
    unsigned char *collisionMask1 = s1->collisionMask;

    int width2 = s2->frames[s2->currentFrame].width;
    int height2 = s2->frames[s2->currentFrame].height;
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
            int ix1 = x - x1;
            int iy1 = y - y1;
            int ix2 = x - x2;
            int iy2 = y - y2;

            int index1 = iy1 * width1 + ix1;
            int index2 = iy2 * width2 + ix2;
            if (collisionMask1[index1] && collisionMask2[index2])
            {
                return 1;
            }
        }
    }
    return 0;
}

void iAnimateSprite(Sprite *sprite)
{
    if (!sprite || sprite->totalFrames <= 1 || !sprite->frames)
        return;

    sprite->currentFrame = (sprite->currentFrame + 1) % sprite->totalFrames;
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

void iLoadFramesFromSheet(Image *frames, const char *filename, int rows, int cols, int ignoreColor = -1)
{
    // Load the sprite sheet image
    Image tmp;
    iLoadImage(&tmp, filename, ignoreColor);

    int frameWidth = tmp.width / cols;
    int frameHeight = tmp.height / rows;
    int totalFrames = cols * rows;

    // Allocate memory for the individual frames
    // frames = new Image[totalFrames];

    // Loop to extract each frame
    for (int i = 0; i < totalFrames; ++i)
    {
        int col = i % cols;
        int row = i / cols;

        // Create an Image structure for each frame
        Image *frame = &frames[i];
        frame->width = frameWidth;
        frame->height = frameHeight;
        frame->channels = tmp.channels;
        frame->data = new unsigned char[frameWidth * frameHeight * frame->channels];

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
}

#define MAX_FILES 1024
#define MAX_FILENAME_LEN 512

void iLoadFramesFromFolder(Image *frames, const char *folderPath, int ignoreColor = -1)
{
    DIR *dir = opendir(folderPath);
    if (dir == nullptr)
    {
        fprintf(stderr, "Failed to open directory: %s\n", folderPath);
        return;
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

    // Load images in sorted order
    for (int i = 0; i < count; ++i)
    {
        char fullPath[MAX_FILENAME_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, filenames[i]);
        iLoadImage(&frames[i], fullPath, ignoreColor);
        free(filenames[i]); // free allocated memory
    }
}

void iInitSprite(Sprite *s)
{
    s->x = 0;
    s->y = 0;

    s->collisionMask = nullptr;
    // s->ignoreColor = ignoreColor;

    // Assign the pre-loaded frames to the sprite
    s->currentFrame = -1;
    s->frames = nullptr;       // Directly assign frames
    s->totalFrames = -1;       // Set the number of frames
    s->scale = 1.0f;           // Initialize scale
    s->flipHorizontal = false; // Initialize flip state
    s->flipVertical = false;   // Initialize flip state
}

void deepCopyImage(Image src, Image *dst)
{
    // Copy the scalar members (width, height, channels)
    dst->width = src.width;
    dst->height = src.height;
    dst->channels = src.channels;
    dst->textureId = 0; // Copy texture ID

    // Allocate memory for the image data in the destination
    dst->data = (unsigned char *)malloc(src.width * src.height * src.channels);
    if (dst->data == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
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
    for (int i = 0; i < s->totalFrames; ++i)
    {
        Image *frame = &s->frames[i];
        iScaleImage(frame, scale);
    }

    iUpdateCollisionMask(s);
}

void iChangeSpriteFrames(Sprite *s, const Image *frames, int totalFrames)
{
    if (s->frames != nullptr)
    {
        for (int i = 0; i < s->totalFrames; ++i)
        {
            iFreeImage(&s->frames[i]);
        }
        delete[] s->frames;
    }

    s->frames = new Image[totalFrames];

    for (int i = 0; i < totalFrames; ++i)
    {
        // printf("PASSED %d\n", i);
        deepCopyImage(frames[i], &s->frames[i]);
    }

    s->currentFrame = 0;
    s->totalFrames = totalFrames;
    s->collisionMask = nullptr;

    // Apply transformations to each frame
    for (int i = 0; i < s->totalFrames; ++i)
    {
        Image *frame = &s->frames[i];
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

void iShowSprite(const Sprite *s)
{
    if (!s || !s->frames)
        return;
    iShowTexture2(s->x, s->y, &s->frames[s->currentFrame]);
}

void iResizeSprite(Sprite *s, int width, int height)
{
    for (int i = 0; i < s->totalFrames; ++i)
    {
        Image *frame = &s->frames[i];
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
    for (int i = 0; i < s->totalFrames; ++i)
    {
        Image *frame = &s->frames[i];
        iMirrorImage(frame, state);
    }
    iUpdateCollisionMask(s);
}

void iFreeSprite(Sprite *s)
{
    for (int i = 0; i < s->totalFrames; ++i)
    {
        iFreeImage(&s->frames[i]);
    }
    delete[] s->frames;
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

int frameCount = 0;
int previousTime = 0;
int fps = 0;

void iShowSpeed(double x, double y)
{
    frameCount++;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;
    if (timeInterval > 1000)
    {
        fps = (frameCount * 1000.0) / timeInterval;
        previousTime = currentTime;
        frameCount = 0;
    }

    char fpsText[20];
    sprintf(fpsText, "FPS: %d", fps);
    iText(x, y, fpsText);
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

bool keys[256] = {false};

void keyboardHandler1FF(unsigned char key, int x, int y)
{
    iKeyboard(key);
    keys[key] = true;
    glutPostRedisplay();
}

void keyboardHandlerUp1FF(unsigned char key, int x, int y)
{
    keys[key] = false;
    glutPostRedisplay();
}

bool isKeyPressed(unsigned char key)
{
    return keys[key];
}

bool specialKeys[109] = {false};

void keyboardHandler2FF(int key, int x, int y)
{
    iSpecialKeyboard(key);
    specialKeys[key] = true; // Mark special key as pressed
    glutPostRedisplay();
}

void keyboardHandlerUp2FF(int key, int x, int y)
{
    specialKeys[key] = false; // Mark special key as released
    glutPostRedisplay();
}

bool isSpecialKeyPressed(int key)
{
    return specialKeys[key];
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
    iMouseWheel(dir, iMouseX, iMouseY);

    glFlush();
}

void iSetTransparency(int state)
{
    transparent = (state == 0) ? 0 : 1;
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
    // iResize(width, height);
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
    glutKeyboardFunc(keyboardHandler1FF);     // normal
    glutKeyboardUpFunc(keyboardHandlerUp1FF); // normal up
    glutSpecialFunc(keyboardHandler2FF);      // special keys
    glutSpecialUpFunc(keyboardHandlerUp2FF);  // special keys up
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
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glutMainLoop();
}
