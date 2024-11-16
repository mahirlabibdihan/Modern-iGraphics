# iGraphics with Extended Features

This is an enhanced version of the iGraphics library, now with support for multiple image formats and new features. Updates will be added incrementally based on requests. Original iGraphics by S. M. Shahriar Nirjon.

Refer to `imageDemo.cpp` and `SpriteDemo.cpp` for examples of the new features.

## New Features
The default `iShowBMP(int x, int y, char filename[])` function reloads the image from disk every time it’s called, causing slowdowns in loops. This is particularly evident when multiple images are rendered to create sprite animation. This extension solves the issue by storing the images in memory.

- **Image Structure**: Load an image once, store it in memory, and reuse it. Reduces file I/O.
  ```c
  typedef struct {
      unsigned char* data;
      int width, height, channels;
  } Image;
  ```

- **Image Functions**:
  - Load an image from a file (supports BMP, PNG, JPG, GIF, PSD, HDR via `stb_image`):
    ```c
    void iLoadImage(Image* img, const char filename[]);
    ```
  - Free image memory:
    ```c
    void iFreeImage(Image* img);
    ```
  - Show, resize, and mirror images. MirrorState can be either `HORIZONTAL` or `VERTICAL`.
    ```c
    void iShowImage(int x, int y, Image* img);
    void iResizeImage(Image* img, int width, int height);
    void iMirrorImage(Image* img, MirrorState state);
    ```

- **Sprite Structure**: Combines image, position, and collision mask.
  ```c
  typedef struct {
      int x, y;
      Image img;
      unsigned char* collisionMask;
      int ignoreColor;
  } Sprite;
  ```

- **Sprite Functions**:
  ```c
  void iLoadSprite(Sprite* s, const char* filename, int ignoreColor);
  void iSetSpritePosition(Sprite* s, int x, int y);
  void iFreeSprite(Sprite* s);
  void iShowSprite(Sprite* s);
  void iResizeSprite(Sprite* s, int width, int height);
  void iMirrorSprite(Sprite* s, MirrorState state);
  ```

## How to Use
1. Include `iGraphics.h` in your project.
2. Edit line 11 in `runner.bat` to match your MinGW directory path.
3. Use `runner.bat your_file_name.c` to compile and run.  
   Executables will be saved in the `exec` folder.
