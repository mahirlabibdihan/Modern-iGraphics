/***
 * iFont.h: v0.1.0
 * A simple font rendering system using FreeType and OpenGL.
 * Provides functions to initialize the font system, render text at specified positions,
 * and free resources.
 * This library is designed to be easy to use for beginners and supports basic text rendering operations.
 * It includes features like loading fonts, rendering text with OpenGL textures, and managing font resources.
 *
 * Author: Mahir Labib Dihan
 * Email: mahirlabibdihan@gmail.com
 * GitHub: https://github.com/mahirlabibdihan
 * Date: July 5, 2025
 */

#include "glut.h"
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library g_ftLibrary;
FT_Face g_ftFace;
bool g_ftInitialized = false;

bool iInitializeFont()
{
    if (g_ftInitialized)
    {
        // printf("Font system already initialized.\n");
        return true;
    }
    if (FT_Init_FreeType(&g_ftLibrary))
    {
        printf("Failed to initialize FreeType.\n");
        return false;
    }

    g_ftInitialized = true;
    return true;
}

// Freetype: https://gnuwin32.sourceforge.net/packages/freetype.htm
// Draw text at position (x, y) using font file `fontName`
void iShowText(double x, double y, const char *text, const char *fontPath, int fontSize = 48)
{
    if (!g_ftInitialized)
    {
        printf("Font system not initialized.\n");
        return;
    }

    if (FT_New_Face(g_ftLibrary, fontPath, 0, &g_ftFace))
    {
        printf("Failed to load font: %s\n", fontPath);
        return;
    }

    FT_Set_Pixel_Sizes(g_ftFace, 0, fontSize);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    float originX = x;
    for (int i = 0; text[i]; i++)
    {
        if (FT_Load_Char(g_ftFace, text[i], FT_LOAD_RENDER))
            continue;

        FT_GlyphSlot g = g_ftFace->glyph;

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer);

        // GLint swizzleMask[] = {GL_ONE, GL_ONE, GL_ONE, GL_RED};
        // glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float xpos = originX + g->bitmap_left;
        float ypos = y - (g->metrics.height / 64.0 - g->bitmap_top); // Account for vertical alignment
        float w = g->bitmap.width;
        float h = g->bitmap.rows;

        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex2f(xpos, ypos);
        glTexCoord2f(1, 1);
        glVertex2f(xpos + w, ypos);
        glTexCoord2f(1, 0);
        glVertex2f(xpos + w, ypos + h);
        glTexCoord2f(0, 0);
        glVertex2f(xpos, ypos + h);
        glEnd();

        originX += (g->advance.x >> 6);

        glDeleteTextures(1, &tex);
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    FT_Done_Face(g_ftFace);
}

void iFreeFont()
{
    if (g_ftInitialized)
    {
        FT_Done_FreeType(g_ftLibrary);
        g_ftInitialized = false;
    }
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <GL/gl.h>

// #define STB_TRUETYPE_IMPLEMENTATION
// #include "stb_truetype.h"

// void render_text_to_opengl(float pos_x, float pos_y, const char *text, const char *font_path, float pixel_height)
// {
//     /* load font file */
//     long size;
//     unsigned char *fontBuffer;

//     FILE *fontFile = fopen(font_path, "rb");
//     if (!fontFile)
//     {
//         printf("Failed to open font file\n");
//         return;
//     }

//     fseek(fontFile, 0, SEEK_END);
//     size = ftell(fontFile);
//     fseek(fontFile, 0, SEEK_SET);

//     fontBuffer = (unsigned char *)malloc(size);
//     fread(fontBuffer, size, 1, fontFile);
//     fclose(fontFile);

//     /* prepare font */
//     stbtt_fontinfo info;
//     if (!stbtt_InitFont(&info, fontBuffer, 0))
//     {
//         printf("Failed to initialize font\n");
//         free(fontBuffer);
//         return;
//     }

//     /* Calculate required dimensions */
//     float scale = stbtt_ScaleForPixelHeight(&info, pixel_height);

//     // First pass to calculate text dimensions
//     int text_width = 0;
//     for (int i = 0; i < strlen(text); ++i)
//     {
//         int ax, lsb;
//         stbtt_GetCodepointHMetrics(&info, text[i], &ax, &lsb);
//         text_width += roundf(ax * scale);

//         if (i < strlen(text) - 1)
//         {
//             text_width += roundf(stbtt_GetCodepointKernAdvance(&info, text[i], text[i + 1]) * scale);
//         }
//     }

//     int x_pos = 0; // Current x position in the bitmap

//     int ascent, descent;
//     stbtt_GetFontVMetrics(&info, &ascent, &descent, NULL);
//     int text_height = roundf((ascent - descent) * scale);
//     ascent = roundf(ascent * scale);
//     descent = roundf(descent * scale);

//     int b_w = text_width;
//     int b_h = text_height;

//     // Round up to nearest power of two
//     // b_w = 1 << (int)ceil(log2(b_w));
//     // b_h = 1 << (int)ceil(log2(b_h));

//     /* create a bitmap for the phrase */
//     unsigned char *bitmap = (unsigned char *)calloc(b_w * b_h, sizeof(unsigned char));

//     /* Render each character to bitmap */
//     for (int i = 0; i < strlen(text); ++i)
//     {
//         /* character metrics */
//         int ax, lsb;
//         stbtt_GetCodepointHMetrics(&info, text[i], &ax, &lsb);

//         /* bounding box */
//         int c_x1, c_y1, c_x2, c_y2;
//         stbtt_GetCodepointBitmapBox(&info, text[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

//         /* compute y position */
//         int y = ascent + c_y1;

//         /* render character */
//         int byteOffset = x_pos + roundf(lsb * scale) + (y * b_w);
//         stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, text[i]);

//         /* advance x */
//         x_pos += roundf(ax * scale);

//         /* add kerning */
//         if (i < strlen(text) - 1)
//         {
//             int kern = stbtt_GetCodepointKernAdvance(&info, text[i], text[i + 1]);
//             x_pos += roundf(kern * scale);
//         }
//     }

//     /* Create and upload OpenGL texture */
//     GLuint texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     /* Basic texture parameters */
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

//     /* Upload as alpha texture */
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, b_w, b_h, 0,
//                  GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);

//     /* Set up rendering state */
//     glEnable(GL_TEXTURE_2D);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     /* Use current color (don't override it) */
//     /* The texture alpha will modulate with current color */

//     /* Calculate text dimensions */
//     // float text_width = x_pos;
//     // float text_height = (ascent - descent);

//     /* Render texture to screen at specified position */
//     glBegin(GL_QUADS);
//     glTexCoord2f(0.0f, 1.0f);
//     glVertex2f(pos_x, pos_y);
//     glTexCoord2f(1.0f, 1.0f);
//     glVertex2f(pos_x + text_width, pos_y);
//     glTexCoord2f(1.0f, 0.0f);
//     glVertex2f(pos_x + text_width, pos_y + text_height);
//     glTexCoord2f(0.0f, 0.0f);
//     glVertex2f(pos_x, pos_y + text_height);
//     glEnd();

//     /* Clean up */
//     glDisable(GL_BLEND);
//     glDisable(GL_TEXTURE_2D);
//     glDeleteTextures(1, &texture);

//     free(fontBuffer);
//     free(bitmap);
// }