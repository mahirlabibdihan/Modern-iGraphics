# iGraphics With Extended Features

This is an extended version of the iGraphics library with multiple image formats support and some additional features. New features will be added incrementally upon request. Original author of iGraphics is S. M. Shahriar Nirjon.

See `imageDemo.cpp` for example usage of the new features.

## Additional Features
- Define new Image structure to store image data. Load once, use multiple times. Reduces File I/O operations.
```
typedef struct{
    unsigned char* data;
    int width, height, channels;
} Image;
```
- Load image from file. Supports multiple image formats (BMP, PNG, JPG, GIF) with the help of the stb_image library.
```
void iLoadImage(Image* img, const char filename[]);
```
- Show image:
```
void iShowImage(int x, int y, Image* img);
```
- Resize image:
```
void iResizeImage(Image* img, int width, int height);
```
- Mirror image: (`MirrorState = HORIZONTAL or VERTICAL`)
```
void iMirrorImage(Image* img, MirrorState state);
```
- Free image:
```
void iFreeImage(Image* img);
```
- Define new Sprite struct to store image, position and collision mask.
```
typedef struct{
    int x, y;
    Image img;
    unsigned char* collisionMask;
    int ignoreColor;
} Sprite;
```
- Sprite functions:
```
void iLoadSprite(Sprite* s, const char* filename, int ignoreColor);
void iSetSpritePosition(Sprite* s, int x, int y);
void iFreeSprite(Sprite* s);
void iShowSprite(Sprite* s);
void iResizeSprite(Sprite* s, int width, int height);
void iMirrorSprite(Sprite* s, MirrorState state);
```
## How to Use
- Include the iGraphics.h header file in your project.
- Change line 11 in runner.bat to the path of MinGW directory in your system.
- Run `runner.bat your_file_name.c` to compile and run your project.
- Executable will be created in the `exec` directory.