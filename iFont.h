/***
 * iFont.h: v0.1.3
 * A simple font rendering system using FreeType and OpenGL.
 * Provides functions to initialize the font system, render text at specified positions,
 * and free resources.
 * This library is designed to be easy to use for beginners and supports basic text rendering operations.
 * It includes features like loading fonts, rendering text with OpenGL textures, and managing font resources.
 *
 * Author: Mahir Labib Dihan
 * Email: mahirlabibdihan@gmail.com
 * GitHub: https://github.com/mahirlabibdihan
 * Date: July 11, 2025
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

uint32_t getNextUTF8Codepoint(const char *&p)
{
    uint32_t codepoint = 0;
    const unsigned char *ptr = (const unsigned char *)p;

    if (*ptr < 0x80)
    {
        codepoint = *ptr;
        p += 1;
    }
    else if ((*ptr & 0xE0) == 0xC0)
    {
        codepoint = (*ptr & 0x1F) << 6;
        codepoint |= (ptr[1] & 0x3F);
        p += 2;
    }
    else if ((*ptr & 0xF0) == 0xE0)
    {
        codepoint = (*ptr & 0x0F) << 12;
        codepoint |= (ptr[1] & 0x3F) << 6;
        codepoint |= (ptr[2] & 0x3F);
        p += 3;
    }
    else if ((*ptr & 0xF8) == 0xF0)
    {
        codepoint = (*ptr & 0x07) << 18;
        codepoint |= (ptr[1] & 0x3F) << 12;
        codepoint |= (ptr[2] & 0x3F) << 6;
        codepoint |= (ptr[3] & 0x3F);
        p += 4;
    }
    else
    {
        p += 1; // invalid byte, skip
    }

    return codepoint;
}

void iShowText(double x, double y, const char *text, const char *fontPath, int fontSize = 32)
{
    if (!iInitializeFont())
    {
        printf("Font system not initialized.\n");
        return;
    }

    if (FT_New_Face(g_ftLibrary, fontPath, 0, &g_ftFace))
    {
        printf("Failed to load font: %s\n", fontPath);
        return;
    }

    FT_Select_Charmap(g_ftFace, FT_ENCODING_UNICODE);
    FT_Set_Pixel_Sizes(g_ftFace, 0, fontSize);

    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    float originX = x;
    const char *p = text;

    while (*p)
    {
        uint32_t codepoint = getNextUTF8Codepoint(p);
        FT_UInt glyph_index = FT_Get_Char_Index(g_ftFace, codepoint);

        if (FT_Load_Glyph(g_ftFace, glyph_index, FT_LOAD_RENDER))
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

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float xpos = originX + g->bitmap_left;
        float ypos = y - (g->metrics.height / 64.0 - g->bitmap_top);
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