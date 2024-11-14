/*
 * bitmap_loader.h
 *
 *  Created on: Jan 8, 2017
 *  Updated on: January 27, 2017
 *      Author: Jisan Mahmud
 */

#pragma warning(disable:4996)
#include <stdio.h>
#define _RGB_TO_INT(rgb) ((rgb).rgbtRed | ((rgb).rgbtGreen << 8) | ((rgb).rgbtBlue << 16))

//
// Puts a BMP image on screen
//
// parameters:
//  x - x coordinate
//  y - y coordinate
//  fileName - name of the BMP file
//  ignoreColor - A specified color that should not be rendered. If you have an
//                image strip that should be rendered on top of another back
//                ground image, then the background of the image strip should
//                not get rendered. Use the background color of the image strip
//                in ignoreColor parameter. Then the strip's background does
//                not get rendered.
//
//                To disable this feature, put -1 in this parameter
//
void iShowBMPAlternative2(int x, int y, char fileName[], int ignoreColor)
{
	FILE *bmpFile;
	if ((bmpFile = fopen(fileName, "rb")) == NULL)
		return;

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);

	int effectiveH = infoHeader.biHeight + (y < 0 ? y : 0);
	int effectiveW = infoHeader.biWidth + (x < 0 ? x : 0);

	if (effectiveH < 1 || effectiveW < 1)
	{
		fclose(bmpFile);
		return;
	}

	int *pixelMap = (int *)malloc(effectiveW * effectiveH * sizeof(int));
	int curPixel, r, c, pixelTrack = 0;
	RGBTRIPLE rgb;
	int alphaSkip = (0xFF << 24);

	for (r = 0; r < infoHeader.biHeight; r++)
	{
		for (c = 0; c < infoHeader.biWidth; c++)
		{
			fread(&rgb, sizeof(rgb), 1, bmpFile);

			if (r >= -y && c >= -x)
			{
				curPixel = _RGB_TO_INT(rgb);
				pixelMap[pixelTrack++] = (curPixel == ignoreColor ? curPixel : curPixel | alphaSkip);
			}
		}
	}

	fclose(bmpFile);

	glRasterPos2f(x < 0 ? 0 : x, y < 0 ? 0 : y);
	glDrawPixels(effectiveW, effectiveH, GL_RGBA, GL_UNSIGNED_BYTE, pixelMap);

	free(pixelMap);
}

//
// Puts a BMP image on screen
//
// parameters:
//  x - x coordinate
//  y - y coordinate
//  fileName - name of the BMP file
//
void iShowBMPAlternative(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, -1);
}

void iShowBMPAlternativeSkipBlack(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, 0);
}

void iShowBMPAlternativeSkipRed(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, 0xFF);
}

void iShowBMPAlternativeSkipGreen(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, (0xFF << 8));
}

void iShowBMPAlternativeSkipBlue(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, (0xFF << 16));
}

void iShowBMPAlternativeSkipWhite(int x, int y, char fileName[])
{
	iShowBMPAlternative2(x, y, fileName, (1 << 24) - 1);
}
