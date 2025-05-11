# Modern iGraphics Library

`iGraphics.h` header file contains some drawing functions that can be used to draw basic graphical shapes in C++. These functions are implemented in OpenGL. Users of iGraphics do not need any knowledge of OpenGL to use it. Simply calling the drawing functions a user can draw any 2D shape on screen. This library also provides easy ways for animation, keyboard and mouse event handling.

It was originally created by [Shahriar Nirjon](https://www.cs.unc.edu/~nirjon/) on 2009 with limited functionalities and only for Windows. This is an extended version of the original iGraphics library with support for multiple image formats, sound engine, sprite management, collision detection and advanced mouse control. The library is now **cross-platform** and works on both Windows and Linux. Besides, the original library used `glut`, which is upgraded to `freeglut` in this version. Updates will be added incrementally based on requests.

---

## ⚙️ Setup

**Download the Library**:
Clone or download the iGraphics library from the repository.

```bash
git clone https://github.com/mahirlabibdihan/Modern-iGraphics
cd Modern-iGraphics
```

Alternatively, you can download the ZIP file from [here](https://github.com/mahirlabibdihan/Modern-iGraphics/archive/refs/heads/main.zip) and extract it.

**Running the Example**:
Ensure that `g++` is installed on your system and available in your PATH. Then, run the following command to compile and execute the example program:

-   **Windows**

```bash
.\runner.bat BallDemo.cpp
```

-   **Linux**

```bash
./runner.sh BallDemo.cpp
```

## 🧱 Setup in Code::Blocks

Open `iGraphics.cbp` in Code::Blocks. The project is already configured with all the necessary settings. You can directly run the project. By default, the main file is `iMain.cpp`. You can remove it and add a different file if you want.

<!-- ### Step 1: Create a New Project

1. `File → New → Project → Empty Project`
2. Give project title: `iGraphics`
3. Edit `Resulting filename` from `....\iGraphics\iGraphics.cbp` to `....\iGraphics.cbp`
4. Keep other things as default and finish.

### Step 2: Add Source File

1. Right-click `Project → Add Files...`
2. Select `iMain.cpp` (or your main file)

### Step 3: Configure Compiler & Linker

#### A. Compiler Settings

1. `Project → Build options...`
2. Go to the **Compiler settings** tab:
    - **Other options** (add these flags):
        ```
        -Wall -fexceptions -g
        ```
    - **Search directories → Compiler** (add these paths):
        ```
        OpenGL\include
        OpenGL\include\irrKlang
        ```

#### B. Linker Settings

1. In the same `Build options` window, go to the **Linker settings** tab.
    - **Other linker options** (add these flags):
        ```
        -static -static-libgcc -static-libstdc++
        ```
    - **Link libraries** (add these libraries):
        ```
        GLU32
        freeglut
        OPENGL32
        gdi32
        winmm
        irrKlang
        ```
    - **Search directories → Linker** (add this path):
        ```
        OpenGL\lib
        ```

### Step 4: Build & Run

-   **F9**: Build & Run
-   **Ctrl+F9**: Build only -->

---

## 👨‍💻 Description of `iMain.cpp`

Users of `iGraphics` only have to edit, compile and run `iMain.cpp`. See the listing of `iMain.cpp` below:

```cpp
#include "iGraphics.h"

/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}
/*

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    //place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int button, int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        //do something with 'q'
    }
    //place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //place your own initialization codes here.
    iInitialize(400, 400, "demooo");
    return 0;
}
```

---

## 🛠️ Functions in `iGraphics.h`

### 🖼️ Graphics Functions

#### `void iInitialize(int width=500, int height=500, char* title="iGraphics")`

-   **Description:** Creates a window of specified size and title.
-   **Parameters:**
    -   `width`: Width of the window.
    -   `height`: Height of the window.
    -   `title`: Title of the window.
-   **Example:**
    ```cpp
    iInitialize(300, 300, "demooo");
    ```

#### `void iClear()`

-   **Description:** Clears the screen.
-   **Parameters:** None
-   **Example:**
    ```cpp
    iClear();
    ```

#### `void iSetColor(int r, int g, int b)`

-   **Description:** Sets current drawing color.
-   **Parameters:**
    -   `r`: Red component of color (0-255).
    -   `g`: Green component of color (0-255).
    -   `b`: Blue component of color (0-255).
-   **Example:**
    ```cpp
    iSetColor(255, 0, 0); // Red
    ```

#### `void iSetTransparentColor(int r, int g, int b, double a)`

-   **Description:** Sets current drawing color with transparency.
-   **Parameters:**
    -   `r`, `g`, `b`: RGB values (0-255).
    -   `a`: Alpha value (0.0 to 1.0).
-   **Example:**
    ```cpp
      iSetTransparentColor(255, 0, 0, 0.5); // Semi-transparent red
    ```

#### `void iGetPixelColor(int x, int y, int rgb[])`

-   **Description:** Gets pixel color at coordinate `(x, y)`.
-   **Parameters:**
    -   `x`, `y`: Coordinates of the pixel.
    -   `rgb[]`: Array to store RGB values.
-   **Example:**
    ```cpp
    iGetPixelColor(100, 120, array);
    ```

#### `void iPoint(double x, double y, int size=0)`

-   **Description:** Draws a point at `(x, y)` using current color.
-   **Parameters:**
    -   `x`, `y`: Coordinates.
    -   `size`: Optional size.
-   **Example:**
    ```cpp
    iPoint(10, 20);
    ```

#### `void iLine(double x1, double y1, double x2, double y2)`

-   **Description:** Draws a line between two points.
-   **Parameters:**
    -   `x1`, `y1`: One end.
    -   `x2`, `y2`: Other end.
-   **Example:**
    ```cpp
    iLine(10, 20, 100, 120);
    ```

#### `void iCircle(double x, double y, double r, int slices=100)`

-   **Description:** Draws a circle.
-   **Parameters:**
    -   `x`, `y`: Center.
    -   `r`: Radius.
    -   `slices`: Segments to draw.
-   **Example:**
    ```cpp
    iCircle(10, 20, 10);
    ```

#### `void iFilledCircle(double x, double y, double r, int slices=100)`

-   **Description:** Draws a filled circle.
-   **Parameters:**
    -   Same as `iCircle`.
-   **Example:**
    ```cpp
    iFilledCircle(10, 20, 10);
    ```

#### `void iEllipse(double x, double y, double a, double b, int slices=100)`

-   **Description:** Draws an ellipse.
-   **Parameters:**
    -   `x`, `y`: Center.
    -   `a`, `b`: Axes lengths.
    -   `slices`: Segments to draw.
-   **Example:**
    ```cpp
    iEllipse(10, 20, 10, 5);
    ```

#### `void iFilledEllipse(double x, double y, double a, double b, int slices=100)`

-   **Description:** Draws a filled ellipse.
-   **Parameters:** Same as `iEllipse`.
-   **Example:**
    ```cpp
    iFilledEllipse(10, 20, 10, 5);
    ```

#### `void iRectangle(double left, double bottom, double dx, double dy)`

-   **Description:** Draws a rectangle.
-   **Parameters:**
    -   `left`: x-coordinate of bottom-left.
    -   `bottom`: y-coordinate of bottom-left.
    -   `dx`: Width.
    -   `dy`: Height.
-   **Example:**
    ```cpp
    iRectangle(10, 20, 10, 5);
    ```

#### `void iFilledRectangle(double left, double bottom, double dx, double dy)`

-   **Description:** Draws a filled-rectangle on the screen with current color.
-   **Parameters:** Same as `iRectangle`.
-   **Example:**
    ```cpp
    iFilledRectangle(10, 20, 10, 5);
    ```

#### `void iPolygon(double x[], double y[], int n)`

-   **Description:** Draws a polygon on the screen with current color.
-   **Parameters:**
    -   `x`, `y`: Arrays of coordinates of vertices.
    -   `n`: Number of vertices.
-   **Example:**
    ```cpp
    double xa[] = {0, 10, 5};
    double ya[] = {0, 0, 10};
    iPolygon(xa, ya, 3);
    ```

#### `void iFilledPolygon(double x[], double y[], int n)`

-   **Description:** Draws a filled-polygon on the screen with current color.
-   **Parameters:** Same as `iPolygon`.
-   **Example:**
    ```cpp
    double xa[] = {0, 10, 5};
    double ya[] = {0, 0, 10};
    iFilledPolygon(xa, ya, 3);
    ```

#### `void iText(GLdouble x, GLdouble y, char *str, void* font=GLUT_BITMAP_8_BY_13)`

-   **Description:** Displays a string on screen.
-   **Parameters:**
    -   `x`, `y`: Coordinates of the first character.
    -   `str`: The text to display.
    -   `font`: (Optional) Font type. Available fonts include:
        -   `GLUT_BITMAP_8_BY_13`
        -   `GLUT_BITMAP_9_BY_15`
        -   `GLUT_BITMAP_TIMES_ROMAN_10`
        -   `GLUT_BITMAP_TIMES_ROMAN_24`
        -   `GLUT_BITMAP_HELVETICA_10`
        -   `GLUT_BITMAP_HELVETICA_12`
        -   `GLUT_BITMAP_HELVETICA_18`
-   **Example:** `iText(50, 60, "This is a text", GLUT_BITMAP_TIMES_ROMAN_10);`

### ⏱️ Animation and Timer

#### `int iSetTimer(int msec, void (*f)(void))`

-   **Description:** Repeatedly executes a function at specified time intervals.
-   **Parameters:**
    -   `msec`: Time interval in milliseconds.
    -   `f`: Function to be executed.
-   **Returns:** Timer index.
-   **Example:**

    ```cpp
    void func() {
        //code of the task that will be repeated.
    }

    int main(int argc, char *argv[])
    {
        ...
        int t = iSetTimer(100, func); // //call it inside main() before iInitialize();
        ...
        iInitialize(400, 400, "demooo");
    }
    ```

#### `void iPauseTimer(int index)`

-   **Description:** Pauses the timer.
-   **Parameters:** `index` of the timer.
-   **Example:** `iPauseTimer(t);`

#### `void iResumeTimer(int index)`

-   **Description:** Resumes the timer.
-   **Parameters:** `index` of the timer.
-   **Example:** `iResumeTimer(t);`

#### `void iDelay(int sec)`

-   **Description:** Pauses execution for a given duration.
-   **Parameters:** `sec` in seconds.
-   **Example:**
    ```cpp
    iDelay(5); // Pauses for 5 seconds
    ```

### 🖼️ Image Functions

-   Load image from file. Supports multiple image formats (BMP, PNG, JPG, GIF) with the help of the stb_image library.

```cpp
bool iLoadImage(Image* img, const char filename[]);
```

-   Show image at position (x, y):

```cpp
void iShowImage(int x, int y, Image* img);
```

-   Wrap an image around the window by `dx` pixels. This function is useful for creating infinite scrolling backgrounds.:

```cpp
void iWrapImage(Image* img, int dx);
```

-   Resize image:

```cpp
void iResizeImage(Image* img, int width, int height);
```

-   Mirror image: (`MirrorState = HORIZONTAL or VERTICAL`)

```cpp
void iMirrorImage(Image* img, MirrorState state);
```

-   Free image:

```cpp
void iFreeImage(Image* img);
```

### 🧩 Sprite Functions

```cpp
void iLoadSprite(Sprite* s, const char* filename, int ignoreColor);
void iLoadSprite(Sprite *s, const char *folderPath, int frameDuration, int ignoreColor);
void iLoadSprite(Sprite *s, const char *filename, int rows, int cols, int startFrame, int endFrame, int frameDuration, int ignoreColor);
void iSetSpritePosition(Sprite* s, int x, int y);
void iShowSprite(Sprite* s);
void iResizeSprite(Sprite* s, int width, int height);
void iMirrorSprite(Sprite* s, MirrorState state);
void iWrapSprite(Sprite* s, int dx);
void iFreeSprite(Sprite* s);
```

### 🔉 Sound Functions

#### `void iPlaySound(const char *filename, bool loop)`

-   **Description:** Plays a sound from file with optional looping.
-   **Parameters:**
    -   `filename`: Path to the sound file.
    -   `loop`: `true` for continuous play, `false` for one-time play.
-   **Example:**
    ```cpp
    iPlaySound("background.wav", true);
    ```

#### `void iStopAllSounds()`

-   **Description:** Stops all currently playing sounds.

### 🧰 Miscellaneous

#### `void iToggleFullscreen()`

-   **Description:** Toggles between fullscreen and windowed mode.

<!-- ## 🖼️ Graphics Functions

### `void iInitialize(int width, int height, const char* title)`

Initializes the OpenGL window with the given dimensions and title.

### `void iClear()`

Clears the screen (called automatically before each `iDraw()` frame).

### `void iSetColor(int r, int g, int b)`

Sets the current drawing color (values from `0` to `255`).

### `void iSetTransparentColor(int r, int g, int b, double a)`

Sets the current drawing color with transparency (values from `0` to `255` for RGB and `0.0` to `1.0` for alpha).

### `void iFilledRectangle(double x, double y, double dx, double dy)`

Draws a filled rectangle at `(x, y)` with width `dx` and height `dy`.

### `void iRectangle(double x, double y, double dx, double dy)`

Draws an outlined rectangle.

### `void iFilledCircle(double x, double y, double r, int slices = 100)`

Draws a filled circle centered at `(x, y)`.

### `void iCircle(double x, double y, double r, int slices = 100)`

Draws an outlined circle.

### `void iLine(double x1, double y1, double x2, double y2)`

Draws a line from `(x1, y1)` to `(x2, y2)`.

### `void iText(double x, double y, const char* str, void* font = GLUT_BITMAP_8_BY_13)`

Renders text at position `(x, y)` using the specified GLUT font.

---

## 🖼️ Image Functions

### `int iLoadImage(const char* filename, int ignoreColor = -1)`

Loads an image from file. Returns an `id` to be used in `iShowImage`.

### `void iShowImage(int x, int y, Image *img)`

Displays an image (loaded with `iLoadImage`) at position `(x, y)` with given size.

### `void iMirrorImage(Image *img, MirrorState state)`

Flips the image horizontally or vertically. MirrorState can be `HORIZONTAL` or `VERTICAL`.

---

## ⏱️ Animation and Timer

### `int iSetTimer(int milliseconds, void (*f)(void))`

Sets a repeating timer that calls function `f()` every `milliseconds`.

### `void iPauseTimer(int timerIndex)`

Pauses the timer specified by `timerIndex`.

### `void iResumeTimer(int timerIndex)`

Resumes a paused timer.

---

## 🕹️ User Input (Callback Interfaces)

### `void iDraw()`

Must be defined by the user. Called every frame to draw graphics.

### `void iMouse(int button, int state, int mx, int my)`

Must be defined by the user. Called on mouse button press/release.

### `void iMouseMove(int mx, int my)`

Must be defined by the user. Called when the mouse moves.

### `void iMouseDrag(int mx, int my)`

Must be defined by the user. Called when the mouse drags.

### `void iMouseWheel(int button, int dir, int mx, int my)`

Must be defined by the user. Called when the mouse wheel is scrolled.

### `void iKeyboard(unsigned char key)`

Must be defined by the user. Called when a keyboard key is pressed.

### `void iSpecialKeyboard(unsigned char key)`

Must be defined by the user. Called when special keys (e.g., arrow keys, F1–F12) are pressed.

---

## 🔉 Sound Functions (Requires irrKlang)

### `void iPlaySound(const char *filename, bool loop)`

Plays a sound from file. `loop = true` for continuous play.

### `void iStopAllSounds()`

Stops all currently playing sounds.

---

## 🧩 Sprite and Collision Utilities

### `int iCheckCollision(Sprite* a, Sprite* b)`

Returns `1` if pixel-level collision is detected between two sprites.

### `Sprite* createSprite(const char* filename)`

Loads an image and creates a sprite structure.

---

## 🧰 Miscellaneous

### `void iDelay(int sec)`

Pauses execution for a given duration.

### `void iToggleFullscreen()`

Toggles between fullscreen and windowed mode.

--- -->

<!-- Contributors -->

---

## ✨ Contributors

| [![Shahriar Nirjon](https://github.com/nirjon.png?size=100)](https://github.com/nirjon) | [![Mahir Labib Dihan](https://github.com/mahirlabibdihan.png?size=100)](https://github.com/mahirlabibdihan) | [![Anwarul Bashar Shuaib](https://github.com/shuaibw.png?size=100)](https://github.com/shuaibw) | [![Ashrafur Rahman Khan](https://github.com/risenfromashes.png?size=100)](https://github.com/risenfromashes) |
| :-------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------: |
|                                   **Shahriar Nirjon**                                   |                                            **Mahir Labib Dihan**                                            |                                    **Anwarul Bashar Shuaib**                                    |                                         **Md. Ashrafur Rahman Khan**                                         |

## 📄 License

This library is for educational purposes and is typically used in academic or hobbyist OpenGL projects.

<!--
## 🙏 Acknowledgements

-   [Extended iGraphics by Ash](https://github.com/risenfromashes/Curves/) - Implementation of cross-platform iGraphics library with additional features.
-   [irrKlang](https://github.com/jonas2602/irrKlang) - The sound engine used for sound playback.
-   [freeglut](https://freeglut.sourceforge.net/) - The OpenGL Utility Toolkit. -->
