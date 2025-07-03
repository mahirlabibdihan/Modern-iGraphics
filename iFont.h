//
//  Original Author: Mahir Labib Dihan
//  last modified: July 3, 2025
//
//  Version: 1.0.0
//

#include "glut.h"
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library g_ftLibrary;
FT_Face g_ftFace;
bool g_ftInitialized = false;

bool iInitFont()
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
            GL_LUMINANCE,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_LUMINANCE,
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
