# iGraphics with Extended Features

This is an enhanced version of the iGraphics library, now with support for multiple image formats and new features. Updates will be added incrementally based on requests. Original iGraphics by S. M. Shahriar Nirjon.

See the following files for example usage of the new features.
- `imageDemo.cpp`
- `SpriteDemo.cpp`
- `MouseDemo.cpp`

## Additional Features
- The `iPassiveMouseMove(int mx, int my)` function is called whenever the mouse moves on the window. The `mx` and `my` parameters are the current x and y coordinates of the mouse cursor on the window. This function can be used to get the coordinate of the mouse cursor on the window without having to click the mouse.

- Define new Image structure to store image data. This structure is used to load the images in memory and display them on the screen without the need of reading from disk  every time.
```cpp
typedef struct{
    unsigned char* data;
    int width, height, channels;
} Image;
```
- Load image from file. Supports multiple image formats (BMP, PNG, JPG, GIF) with the help of the stb_image library.
```cpp
void iLoadImage(Image* img, const char filename[]);
```
- Show image at position (x, y):
```cpp
void iShowImage(int x, int y, Image* img);
```
- Wrap an image around the window by `dx` pixels. This function is useful for creating infinite scrolling backgrounds.:
```cpp
void iWrapImage(Image* img, int dx);
```
- Resize image:
```cpp
void iResizeImage(Image* img, int width, int height);
```
- Mirror image: (`MirrorState = HORIZONTAL or VERTICAL`)
```cpp
void iMirrorImage(Image* img, MirrorState state);
```
- Free image:
```cpp
void iFreeImage(Image* img);
```
- Define new Sprite struct to store image, position and collision mask. The functionalities of the Sprite struct are similar to the Image struct with additional features like setting positions and collision detection.
```cpp
typedef struct{
    int x, y;
    Image img;
    unsigned char* collisionMask;
    int ignoreColor;
} Sprite;
```
- The main difference with loading with the `Sprite` struct is that an `ignorecolor` parameter is passed during loading. Set this to `-1` to read the whole image, or `0xRRGGBB` to ignore the color `RRGGBB` while loading the image. The ignored part will be transparent. The collision mask is also generated during loading (`iLoadSprite` internally calls the `iUpdateCollisionMask` function), so there is no need to set it manually unless you want to change it.
```cpp
void iLoadSprite(Sprite* s, const char* filename, int ignoreColor);
void iSetSpritePosition(Sprite* s, int x, int y);
void iFreeSprite(Sprite* s);
void iShowSprite(Sprite* s);
void iWrapSprite(Sprite* s, int dx);
void iResizeSprite(Sprite* s, int width, int height);
void iMirrorSprite(Sprite* s, MirrorState state);
```

- The collision detection is handled by the `int iCheckCollision(Sprite* s1, Sprite* s2)` function. Returns `1` or `0` depending on whether the two sprites are colliding or not. If the bounding box of two images do not overlap, this has a time complexity of `O(1)`. Otherwise, it has a time complexity of `O(wh)`, where `w` and `h` are the width and height of the overlapping area of the two images. Internally, whenever a sprite is created, it automatically creates a collision mask, which is a boolean 2D array of the same size as the image. 


## How to Use
- Include the `iGraphics.h` header file in your project.
- Change line 11 in runner.bat to the path of MinGW directory in your system.
- Run `runner.bat your_file_name.cpp` to compile and run your project.
- Executable will be created in the `exec` directory.