<div align="center">
<h1> Modern iGraphics Library</h1>
<h2> 🎮 A Comprehensive C++ Graphics Library for Beginners</h2>
</div>

<p align="center">
    <a href="https://github.com/mahirlabibdihan/Modern-iGraphics">
      <img src="https://img.shields.io/badge/GitHub-Repo-black?logo=github&&style=for-the-badge" alt="GitHub repo"/>
    </a>
    <a href="https://github.com/mahirlabibdihan/Modern-iGraphics/stargazers">
      <img src="https://img.shields.io/github/stars/mahirlabibdihan/Modern-iGraphics.svg?style=for-the-badge" alt="GitHub stars"/>
    </a>
    <a href="https://github.com/mahirlabibdihan/Modern-iGraphics/network/members">
      <img src="https://img.shields.io/github/forks/mahirlabibdihan/Modern-iGraphics.svg?style=for-the-badge" alt="GitHub forks"/>
    </a>
     <a href="https://github.com/mahirlabibdihan/Modern-iGraphics/commits/main/">
     <img src="https://img.shields.io/github/last-commit/mahirlabibdihan/Modern-iGraphics?style=for-the-badge" alt="Last Commit"/>
     </a>
    <a href="https://github.com/mahirlabibdihan/Modern-iGraphics/releases/latest">
     <img src="https://img.shields.io/github/v/release/mahirlabibdihan/Modern-iGraphics?style=for-the-badge" alt="Latest Release"/>
     </a>

</p>

<!-- --- -->

<!-- Banner Image -->

<div align="center">
    <img src="banner.svg" alt="iGraphics Banner" width="600">
</div>

<!-- --- -->

<!--
[![GitHub Repo](https://img.shields.io/badge/GitHub-Repo-black?logo=github)](https://github.com/mahirlabibdihan/Modern-iGraphics) -->

<!-- [![GitHub stars](https://img.shields.io/github/stars/mahirlabibdihan/Modern-iGraphics.svg?style=for-the-badge)](https://github.com/mahirlabibdihan/Modern-iGraphics/stargazers)

[![GitHub forks](https://img.shields.io/github/forks/mahirlabibdihan/Modern-iGraphics.svg?style=for-the-badge)](https://github.com/mahirlabibdihan/Modern-iGraphics/fork) -->

<!-- <a href="https://github.com/mahirlabibdihan/Modern-iGraphics">💻 Code</a>
    <a href="https://mahirlabibdihan.github.io/Modern-iGraphics">🏠 Homepage</a> -->

<!-- --- -->

<br>

[iGraphics.h](https://igraphics2d.blogspot.com/p/igraphics-documentation.html) header file contains some drawing functions that can be used to draw basic graphical shapes in C++. These functions are implemented in OpenGL. Users of iGraphics do not need any knowledge of OpenGL to use it. Simply calling the drawing functions a user can draw any 2D shape on screen. This library also provides easy ways for animation, keyboard and mouse event handling.

It was originally created by [Shahriar Nirjon](https://www.cs.unc.edu/~nirjon/) on 2009 with limited functionalities and only for Windows. This is an extended version of the original iGraphics library with support for multiple image formats, custom fonts, sound engine, sprite management, collision detection and advanced mouse-keyboard control. The library is now **cross-platform** and works on both **Windows** and **Linux**. Updates will be added incrementally based on requests.

## 🧱 Original iGraphics vs. ⚙️ Modern iGraphics

<!-- <div align="center"> -->

| **Feature**                | **Original iGraphics (2009)** | **Modern iGraphics (2025)**       |
| :------------------------- | :---------------------------- | :-------------------------------- |
| **Cross-Platform Support** | ❌ Windows only               | ✅ Windows & Linux                |
| **Image Formats**          | ❌ BMP only                   | ✅ Multiple formats               |
| **Audio Formats**          | ❌ WAV only                   | ✅ Multiple formats               |
| **Font Support**           | ❌ Limited bitmap fonts       | ✅ Custom TTF fonts               |
| **Sound Integration**      | ❌ Single Channel             | ✅ Multi-Channel                  |
| **Input Handling**         | ❌ Basic                      | ✅ Enhanced controls              |
| **Transparency Support**   | ❌ Not available              | ✅ Full RGBA color support        |
| **Image Manipulation**     | ❌ No transformations         | ✅ Rotate/Scale/Flip/Wrap         |
| **Image rendering**        | ❌ Slow                       | ✅ Fast (Texture-based + Caching) |
| **Sprite Management**      | ❌ Manual implementation      | ✅ Built-in sprite system         |
| **Collision Detection**    | ❌ Not available              | ✅ Pixel-perfect collision        |

<!-- </div> -->
<!-- Besides, the original library used `glut`, which is upgraded to `freeglut` in this version. -->

---

<!-- Youtube Demo -->

## 🎥 Example Games

- [DxBall](https://youtu.be/J9kCPZOhV7A?si=nP5pI-Xvn4eHt2Tw)
- [Platformer Game](https://youtu.be/Fb0ucPYe3sE?si=vNgahtO5K5mCn1Eb)
- [Flappy Bird](https://youtu.be/hjveGbF3tzE?si=M9HfChSBx1hdfUtU)
- [Chess](https://youtu.be/8GeTDn3IZIY?si=hjPXHMog1PPCoPAI)
- [Tetris](https://youtu.be/jC8eX8RNuUM?si=ai22EmpSUbyJSyTN)
- [Snake Game](https://youtu.be/mjOVhspXOjY?si=VVC-PrjMz3F79m_f)

You can find executable games [here](https://github.com/mahirlabibdihan/Modern-iGraphics/releases/download/v0.0.1/demo.zip)

---

## Necessary Files

- Download the `Modern-iGraphics-main.zip` file from [here](https://github.com/mahirlabibdihan/Modern-iGraphics/archive/refs/heads/main.zip) and extract it.
- Download `MINGW.zip` file from [here](https://github.com/mahirlabibdihan/Modern-iGraphics/releases/download/v0.0.1/MINGW.zip) and extract it.
- Copy the `MINGW` folder to the extracted `Modern-iGraphics-main` folder.
- The final folder structure should look like this:

```
Modern-iGraphics-main
├── MINGW
│   ├── bin
│   ├── include
│   ├── lib
│   ├── ....
│   └── share
├── OpenGL
├── assets
├── bin
├── obj
├── examples
├── iGraphics.h
├── iGraphics.cbp
├── iMain.cpp
├── ....
```

## 🧱 Setup in Code::Blocks

Change the compiler path of Code::Blocks as following:
`Settings` → `Compiler` → Go to `Toolchain executables` tab → Change the `Compiler's installation directory` to the `MINGW` directory in the iGraphics folder. You can do that by clicking the three dots (`...`) on right. After you change the compiler, clear the `.o` files inside `obj` folder (If there is any).

Open `iGraphics.cbp` in Code::Blocks. The project is already configured with all the necessary settings. You can directly run the project. By default, the main file is `iMain.cpp`. You can remove it and add a different file if you want.

_You can find the slides with step-by-step screenshots_ [here](https://docs.google.com/presentation/d/1VTaBzzTKQhPsGCA9_CBIUZvDUh3l6v3_gnTCPSLk_XM/edit?usp=sharing).

---

## ⚙️ Setup in Terminal

**Download the Library**:
Clone or download the iGraphics library from the repository.

```bash
git clone https://github.com/mahirlabibdihan/Modern-iGraphics
cd Modern-iGraphics
```

Alternatively, you can download the ZIP file from [here](https://github.com/mahirlabibdihan/Modern-iGraphics/archive/refs/heads/main.zip) and extract it.

**Running the Example**:
Ensure that `g++` is installed on your system and available in your PATH. Then, run the following command to compile and execute the example program:

- **Windows**

```bash
.\runner.bat examples\BallDemo.cpp
```

- **Linux**

```bash
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt install libsdl2-dev libsdl2-mixer-dev
sudo apt install libfreetype6-dev
./runner.sh examples/BallDemo.cpp
```

---

## 🚀 Quick Start

### 🛠️ Project Creation Tools

For quick project setup, use the provided project creation scripts:

**Windows:**

```bash
.\create_project.bat MyGameName
```

**Linux/Unix:**

```bash
./create_project.sh MyGameName
```

These scripts will automatically generate a complete starter template with:

- ✅ All necessary iGraphics function stubs
- ✅ Example drawing code (text + red circle)
- ✅ Mouse and keyboard handlers
- ✅ Animation timer setup (commented)
- ✅ Comprehensive comments and documentation

---

<!-- Release Guideline -->

## 📦 Release Guideline (Windows)

- **Organize Your Assets**

  - Ensure all game assets (images, sprites, sounds, level designs, etc.) are inside the assets folder.
  - Remove any unnecessary or default assets to save space.

- **Save Files**

  - Place any saved game data in the saves folder.

- **Run the Release Script**

  - Double-click release.bat or run it from the terminal using:
    `.\release.bat iMain.cpp`

- **Check the Output**
  - After execution, a release folder will be created. Navigate to:
    `release → windows → x86`
  - Inside, you’ll find the necessary files to run your game. Please test `game.exe` to ensure your game runs properly.

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
        .
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

Users of `iGraphics` only have to edit, compile and run [iMain.cpp](https://github.com/mahirlabibdihan/Modern-iGraphics/blob/main/iMain.cpp). See the listing of `iMain.cpp` below:

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
function iMouseClick() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
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
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
function iKeyPress() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case 'q':
        // do something with 'q'
        iCloseWindow();
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

/*
function iSpecialKeyPress() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyPress(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    // Initialization code before opening the window
    iOpenWindow(400, 400, "iGraphics");
    // Execution will continue from here once iCloseWindow() is called.
    return 0;
}
```

---

## 🛠️ Functions in `iGraphics.h`

### 🖼️ Graphics Functions

#### `void iOpenWindow(int width=500, int height=500, char* title="iGraphics")`

- **Description:** Creates a window of specified size and title.
- **Parameters:**
  - `width`: Width of the window.
  - `height`: Height of the window.
  - `title`: Title of the window.
- **Example:**
  ```cpp
  iOpenWindow(300, 300, "iGraphics");
  ```

#### `void iCloseWindow()`

- **Description:** Closes the current window.
- **Parameters:** None
- **Example:**
  ```cpp
  void iKeyPress(unsigned char key)
  {
      switch (key)
      {
      case 'q':
          iCloseWindow();
          break;
      default:
          break;
      }
  }
  ```

#### `void iClear()`

- **Description:** Clears the screen.
- **Parameters:** None
- **Example:**
  ```cpp
  iClear();
  ```

#### `void iSetColor(int r, int g, int b)`

- **Description:** Sets current drawing color.
- **Parameters:**
  - `r`: Red component of color (0-255).
  - `g`: Green component of color (0-255).
  - `b`: Blue component of color (0-255).
- **Example:**
  ```cpp
  iSetColor(255, 0, 0); // Red
  ```

#### `void iSetTransparentColor(int r, int g, int b, double a)`

- **Description:** Sets current drawing color with transparency.
- **Parameters:**
  - `r`, `g`, `b`: RGB values (0-255).
  - `a`: Alpha value (0.0 to 1.0).
- **Example:**
  ```cpp
    iSetTransparentColor(255, 0, 0, 0.5); // Semi-transparent red
  ```

#### `void iGetPixelColor(int x, int y, int rgb[])`

- **Description:** Gets pixel color at coordinate `(x, y)`.
- **Parameters:**
  - `x`, `y`: Coordinates of the pixel.
  - `rgb[]`: Array to store RGB values.
- **Example:**
  ```cpp
  iGetPixelColor(100, 120, array);
  ```

#### `void iPoint(double x, double y, int size=0)`

- **Description:** Draws a point at `(x, y)` using current color.
- **Parameters:**
  - `x`, `y`: Coordinates.
  - `size`: Optional size.
- **Example:**
  ```cpp
  iPoint(10, 20);
  ```

#### `void iLine(double x1, double y1, double x2, double y2)`

- **Description:** Draws a line between two points.
- **Parameters:**
  - `x1`, `y1`: One end.
  - `x2`, `y2`: Other end.
- **Example:**
  ```cpp
  iLine(10, 20, 100, 120);
  ```

#### `void iCircle(double x, double y, double r, int slices=100)`

- **Description:** Draws a circle.
- **Parameters:**
  - `x`, `y`: Center.
  - `r`: Radius.
  - `slices`: Segments to draw.
- **Example:**
  ```cpp
  iCircle(10, 20, 10);
  ```

#### `void iFilledCircle(double x, double y, double r, int slices=100)`

- **Description:** Draws a filled circle.
- **Parameters:**
  - Same as `iCircle`.
- **Example:**
  ```cpp
  iFilledCircle(10, 20, 10);
  ```

#### `void iEllipse(double x, double y, double a, double b, int slices=100)`

- **Description:** Draws an ellipse.
- **Parameters:**
  - `x`, `y`: Center.
  - `a`, `b`: Axes lengths.
  - `slices`: Segments to draw.
- **Example:**
  ```cpp
  iEllipse(10, 20, 10, 5);
  ```

#### `void iFilledEllipse(double x, double y, double a, double b, int slices=100)`

- **Description:** Draws a filled ellipse.
- **Parameters:** Same as `iEllipse`.
- **Example:**
  ```cpp
  iFilledEllipse(10, 20, 10, 5);
  ```

#### `void iRectangle(double left, double bottom, double dx, double dy)`

- **Description:** Draws a rectangle.
- **Parameters:**
  - `left`: x-coordinate of bottom-left.
  - `bottom`: y-coordinate of bottom-left.
  - `dx`: Width.
  - `dy`: Height.
- **Example:**
  ```cpp
  iRectangle(10, 20, 10, 5);
  ```

#### `void iFilledRectangle(double left, double bottom, double dx, double dy)`

- **Description:** Draws a filled-rectangle on the screen with current color.
- **Parameters:** Same as `iRectangle`.
- **Example:**
  ```cpp
  iFilledRectangle(10, 20, 10, 5);
  ```

#### `void iPolygon(double x[], double y[], int n)`

- **Description:** Draws a polygon on the screen with current color.
- **Parameters:**
  - `x`, `y`: Arrays of coordinates of vertices.
  - `n`: Number of vertices.
- **Example:**
  ```cpp
  double xa[] = {0, 10, 5};
  double ya[] = {0, 0, 10};
  iPolygon(xa, ya, 3);
  ```

#### `void iFilledPolygon(double x[], double y[], int n)`

- **Description:** Draws a filled-polygon on the screen with current color.
- **Parameters:** Same as `iPolygon`.
- **Example:**
  ```cpp
  double xa[] = {0, 10, 5};
  double ya[] = {0, 0, 10};
  iFilledPolygon(xa, ya, 3);
  ```

#### `void iSetLineWidth(float width)`

- **Description:** Sets the width of lines to be drawn.
- **Parameters:** `width` - Line width in pixels.
- **Example:**
  ```cpp
  iSetLineWidth(3.0); // Set line width to 3 pixels
  iLine(0, 0, 100, 100); // Draw a thick line
  ```

#### `void iShowSpeed(double x, double y)`

- **Description:** Displays the current FPS (Frames Per Second) at specified coordinates.
- **Parameters:**
  - `x`, `y`: Coordinates where FPS will be displayed.
- **Example:**
  ```cpp
  iShowSpeed(10, 10); // Show FPS counter at top-left corner
  ```

#### `void iText(double x, double y, char *str, void* font=GLUT_BITMAP_8_BY_13)`

- **Description:** Displays a string on screen.
- **Parameters:**
  - `x`, `y`: Coordinates of the first character.
  - `str`: The text to display.
  - `font`: (Optional) Font type. Available fonts include:
    - `GLUT_BITMAP_8_BY_13`
    - `GLUT_BITMAP_9_BY_15`
    - `GLUT_BITMAP_TIMES_ROMAN_10`
    - `GLUT_BITMAP_TIMES_ROMAN_24`
    - `GLUT_BITMAP_HELVETICA_10`
    - `GLUT_BITMAP_HELVETICA_12`
    - `GLUT_BITMAP_HELVETICA_18`
- **Example:** `iText(50, 60, "This is a text", GLUT_BITMAP_TIMES_ROMAN_10);`

#### `void iRotate(double x, double y, double degree)`

- **Description:** Rotates the coordinate system around a point.
- **Parameters:**
  - `x`, `y`: Coordinates of the point to rotate around.
  - `degree`: Angle in degrees to rotate.
- **Example:**
  ```cpp
  iRotate(100, 100, 45); // Rotate around point (100, 100) by 45 degrees
  iShowImage(50, 50, "image.png"); // This image will be rotated
  iUnRotate();
  ```

#### `void iScale(double x, double y, double scaleX, double scaleY)`

- **Description:** Scales the coordinate system around a point.
- **Parameters:**
  - `x`, `y`: Coordinates of the point to scale around.
  - `scaleX`: Scaling factor in the x-direction.
  - `scaleY`: Scaling factor in the y-direction.
  - **Example:**
  ```cpp
  iScale(0,0, 2.0, 1.5); // Scale around the origin (0, 0) by 2.0 in x and 1.5 in y
  // This will affect all subsequent drawing operations
  iUnScale();
  ```

### ⏱️ Animation and Timer

#### `int iSetTimer(int msec, void (*f)(void))`

- **Description:** Repeatedly executes a function at specified time intervals.
- **Parameters:**
  - `msec`: Time interval in milliseconds.
  - `f`: Function to be executed.
- **Returns:** Timer index.
- **Example:**

  ```cpp
  void func() {
      //code of the task that will be repeated.
  }

  int main(int argc, char *argv[])
  {
      ...
      int t = iSetTimer(100, func); // //call it inside main() before iOpenWindow();
      ...
      iOpenWindow(400, 400, "iGraphics");
  }
  ```

#### `void iPauseTimer(int index)`

- **Description:** Pauses the timer.
- **Parameters:** `index` of the timer.
- **Example:** `iPauseTimer(t);`

#### `void iResumeTimer(int index)`

- **Description:** Resumes the timer.
- **Parameters:** `index` of the timer.
- **Example:** `iResumeTimer(t);`

#### `void iDelay(int sec)`

- **Description:** Pauses execution for a given duration.
- **Parameters:** `sec` in seconds.
- **Example:**
  ```cpp
  iDelay(5); // Pauses for 5 seconds
  ```

### 🖱️ Mouse Functions

#### `void iMouseClick(int button, int state, int mx, int my)`

- **Description:** Called when a mouse button is pressed or released.
- **Parameters:**
  - `button`: Button pressed (GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON).
  - `state`: State of the button (GLUT_DOWN or GLUT_UP).
  - `mx`, `my`: Coordinates of the mouse pointer.
- **Note:** _This function should be defined in the main file._

#### `void iMouseMove(int mx, int my)`

- **Description:** Called when the mouse moves.
- **Parameters:** `mx`, `my`: Coordinates of the mouse pointer.
- **Note:** _This function should be defined in the main file._

#### `void iMouseDrag(int mx, int my)`

- **Description:** Called when the mouse is dragged.
- **Parameters:** `mx`, `my`: Coordinates of the mouse pointer.
- **Note:** _This function should be defined in the main file._

#### `void iMouseWheel(int dir, int mx, int my)`

- **Description:** Called when the mouse wheel is scrolled.
- **Parameters:**
  - `dir`: Direction of scroll (1 for up, -1 for down).
  - `mx`, `my`: Coordinates of the mouse pointer.
- **Note:** _This function should be defined in the main file._

#### `void iShowCursor()`

- **Description:** Shows the mouse cursor.
- **Parameters:** None
- **Example:**
  ```cpp
  iShowCursor();
  ```

#### `void iHideCursor()`

- **Description:** Hides the mouse cursor.
- **Parameters:** None
- **Example:**
  ```cpp
  iHideCursor();
  ```

### ⌨️ Keyboard Functions

#### `void iKeyPress(unsigned char key)`

- **Description:** Called when a key is pressed.
- **Parameters:**
  - `key`: ASCII value of the key pressed.
- **Note:** _This function should be defined in the main file._

#### `void iSpecialKeyPress(unsigned char key)`

- **Description:** Called when a special key is pressed.
- **Parameters:**
  - `key`: Special key value (e.g., `GLUT_KEY_LEFT`, `GLUT_KEY_RIGHT`, etc.).
- **Note:** _This function should be defined in the main file._

#### `void iKeyRelease(unsigned char key)`

- **Description:** Called when a key is released.
- **Parameters:**
- `key`: ASCII value of the key released.
- **Note:** _This function should be defined in the main file._

#### `void iSpecialKeyRelease(unsigned char key)`

- **Description:** Called when a special key is released.
- **Parameters:**
- `key`: Special key value (e.g., `GLUT_KEY_LEFT`, `GLUT_KEY_RIGHT`, etc.).
- **Note:** _This function should be defined in the main file._

#### `int isKeyPressed(unsigned char key)`

- **Description:** Checks if a key is being pressed (Not yet released).
- **Parameters:** `key` to check.
- **Returns:** `1` if pressed, `0` otherwise.
- **Example:**
  ```cpp
  if (isKeyPressed('a')) {
      // 'a' key is pressed
  }
  ```

#### `int isSpecialKeyPressed(unsigned char key)`

- **Description:** Checks if a special key is being pressed (Not yet released).
- **Parameters:** `key` to check.
- **Returns:** `1` if pressed, `0` otherwise.
- **Example:**
  ```cpp
  if (isSpecialKeyPressed(GLUT_KEY_LEFT)) {
      // Left arrow key is pressed
  }
  ```

### 🔉 Sound Functions

`iGraphics` was originally designed for graphical applications, but it has been extended to support sound playback using the `SDL2` library. The sound functions are available in `iSound.h` and are shown below:

#### `int iPlaySound(const char *filename, int loop = 0, int volume = 100)`

- **Description:** Plays a sound from file with optional looping and volume control.
- **Parameters:**
  - `filename`: Path to the sound file.
  - `loop`: `true` for continuous play, `false` for one-time play.
  - `volume`: Volume level (0-100).
- **Returns:** Channel where the sound is played (-1 if failed).
- **Note:** You can't play more than 8 sounds simultaneously.
- **Supported Formats:** WAV, MP3, OGG, FLAC, and more.
- **Example:**

  ```cpp
  #include "iSound.h" // Include the sound header
  ...
  int channel = iPlaySound("background.wav", true, 80);
  ```

#### `void iPauseSound(int channel)`

- **Description:** Pauses the sound specified by `channel`.
- **Parameters:** `channel` of the sound.
- **Example:**
  ```cpp
  iPauseSound(channel);
  ```

#### `void iResumeSound(int channel)`

- **Description:** Resumes the sound specified by `channel`.
- **Parameters:** `channel` of the sound.
- **Example:**
  ```cpp
  iResumeSound(channel);
  ```

#### `void iStopSound(int channel)`

- **Description:** Stops the sound specified by `channel`. Frees the channel for other sounds.
- **Parameters:** `channel` of the sound.
- **Example:**
  ```cpp
  iStopSound(channel);
  ```

#### `void iStopAllSounds()`

- **Description:** Stops all currently playing sounds. Frees all channels.

#### `void iSetVolume(int channel, int volume)`

- **Description:** Sets the volume for a specific sound.
- **Parameters:**
  - `index`: Index of the sound.
  - `volume`: Volume level (0-100).

#### `void iIncreaseVolume(int channel, int amount)`

- **Description:** Increases the volume of a specific sound by a specified amount.
- **Parameters:**
  - `index`: Index of the sound.
  - `amount`: Amount to increase the volume by (0-100).

#### `void iDecreaseVolume(int channel, int amount)`

- **Description:** Decreases the volume of a specific sound by a specified amount.
- **Parameters:**
  - `index`: Index of the sound.
  - `amount`: Amount to decrease the volume by (0-100).

### 🅰️ Text Functions

Custom font rendering is supported using TrueType fonts. `freetype` library is used to render text. The new text functions are available in `iFont.h` and are shown below:

#### `void iShowText(double x, double y, const char *text, const char *fontPath, int fontSize = 48)`

- **Description:** Displays a string on screen using TrueType font.
- **Parameters:**
  - `x`, `y`: Coordinates of the first character.
  - `text`: The text to display.
  - `fontPath`: Path to the TrueType font file (e.g., "assets/fonts/arial.ttf").
  - `fontSize`: Size of the font (default is 48).
- **Example:**

  ```cpp
  #include "iFont.h" // Include the font header
  ...
  iShowText(50, 60, "This is a text", "assets/fonts/arial.ttf", 48);
  ```

### 🖼️ Image Functions

#### `void iShowImage(int x, int y, const char *filename)`

- **Description:** Displays an image at specified coordinates.
- **Parameters:**

  - `x`, `y`: Coordinates where the image will be displayed.
  - `filename`: Path to the image file.

- **Example:**
  ```cpp
  iShowImage(100, 200, "image.png");
  ```

#### `int iLoadImage(Image* img, const char filename[])`

- **Description:** Loads an image from file. Supports multiple image formats (BMP, PNG, JPG, GIF) with the help of the stb_image library.

- **Parameters:**

  - `img`: Pointer to an `Image` structure.
  - `filename`: Path to the image file.
  <!-- - `ignoreColor`: Color to be ignored (default is -1, which means no color is ignored). If set to `0xRRGGBB`, it will ignore the color `RRGGBB` while loading the image (e.g., `0xFF0000` for red). -->

- **Returns:** `true` if successful, `false` otherwise.
- **Example:**
  ```cpp
  Image img;
  if (iLoadImage(&img, "image.png")) {
      // Image loaded successfully
  } else {
      // Failed to load image
  }
  ```
- **Image Structure**
  ```cpp
  typedef struct
  {
      unsigned char *data;
      int width, height, channels;
      GLuint textureID; // OpenGL texture ID
  } Image;
  ```

#### `void iShowLoadedImage(int x, int y, Image* img)`

- **Description:** Displays an already loaded image at specified coordinates. Image should be loaded using `iLoadImage`.
- **Parameters:**

  - `x`, `y`: Coordinates where the image will be displayed.
  - `img`: Pointer to the loaded `Image` structure.

- **Example:**

  ```cpp
  Image img;
  iLoadImage(&img, "image.png");
  iShowLoadedImage(100, 200, &img);
  ```

#### `void iScaleImage(Image* img, double scale)`

- **Description:** Scales the image by a specified factor.
- **Parameters:**

  - `img`: Pointer to the loaded `Image` structure.
  - `scale`: Scaling factor (e.g., 2.0 for double size).

- **Example:** `iScaleImage(&img, 2.0);`

#### `void iResizeImage(Image* img, int width, int height)`

- **Description:** Resizes the image to specified dimensions.
- **Parameters:**
  - `img`: Pointer to the loaded `Image` structure.
  - `width`: New width of the image.
  - `height`: New height of the image.
- **Example:**

  ```cpp
  iResizeImage(&img, 200, 100); // Resize to 200x100 pixels
  ```

#### `void iMirrorImage(Image* img, MirrorState state)`

- **Description:** Mirrors the image either horizontally or vertically.
- **Parameters:**

  - `img`: Pointer to the loaded `Image` structure.
  - `state`: `HORIZONTAL` or `VERTICAL`. Here, MirrorState is an enum.

- **Example:**

  ```cpp
  iMirrorImage(&img, HORIZONTAL); // Mirror horizontally
  ```

#### `void iWrapImage(Image* img, int dx = 0, int dy = 0)`

- **Description:** Wraps the image around the screen by `dx` pixels horizontally and `dy` pixels vertically. This function is useful for creating infinite scrolling backgrounds.
- **Parameters:**
  - `img`: Pointer to the loaded `Image` structure.
  - `dx`: Horizontal shift in pixels (default is 0).
    - A positive value of `dx` shifts the image to the right.
    - A negative value of `dx` shifts the image to the left.
  - `dy`: Vertical shift in pixels (default is 0).
    - A positive value of `dy` shifts the image down.
    - A negative value of `dy` shifts the image up.
- **Example:**

  ```cpp
  iWrapImage(&img, 50); // Wrap the image by 50 pixels to the right
  iWrapImage(&img, -50); // Wrap the image by 50 pixels to the left
  iWrapImage(&img, 0, 30); // Wrap the image by 30 pixels down
  iWrapImage(&img, 0, -30); // Wrap the image by 30 pixels up
  ```

#### `void iIgnorePixels(Image* img, int ignoreColor)`

- **Description:** Makes specific colored pixels transparent in the image.
- **Parameters:**
  - `img`: Pointer to the loaded `Image` structure.
  - `ignoreColor`: Color to ignore in 0xRRGGBB format (e.g., 0xFF0000 for red).
- **Example:**
  ```cpp
  iIgnorePixels(&img, 0xFFFFFF); // Make white pixels transparent
  ```

#### `void iFreeImage(Image* img)`

- **Description:** Frees the memory allocated for the image.

<!-- SVG FUnctions -->

<!-- ### 📊 SVG Functions

#### `void iShowSVG(int x, int y, const char *filename, double scale = 1.0, MirrorState mirror = NO_MIRROR)`

- **Description:** Displays an SVG image at specified coordinates.
- **Parameters:**
  - `x`, `y`: Coordinates where the SVG will be displayed.
  - `filename`: Path to the SVG file.
  - `scale`: Scaling factor (default is 1.0).
  - `mirror`: Mirror state (default is `NO_MIRROR`).
- **Example:**
  ```cpp
  iShowSVG(100, 200, "image.svg", 1.5, HORIZONTAL);
  ```

#### `bool iLoadSVG(SVG *svg, const char *filename, double scale = 1.0)`

- **Description:** Loads an SVG image from file.
- **Parameters:**
  - `svg`: Pointer to an `SVG` structure.
  - `filename`: Path to the SVG file.
  - `scale`: Scaling factor (default is 1.0).
  - **Returns:** `true` if successful, `false` otherwise.
  - **Example:**
  ```cpp
  Image svg;
  if (iLoadSVG(&svg, "image.svg", 1.5)) {
      // SVG loaded successfully
  } else {
      // Failed to load SVG
  }
  ```

#### `void iShowLoadedSVG(int x, int y, Image *svg, MirrorState mirror = NO_MIRROR)`

- **Description:** Displays an already loaded SVG image at specified coordinates.
- **Parameters:**
  - `x`, `y`: Coordinates where the SVG will be displayed.
  - `svg`: Pointer to the loaded svg image.
  - `mirror`: Mirror state (default is `NO_MIRROR`).
- **Example:**
  ```cpp
  Image svg;
  iLoadSVG(&svg, "image.svg", 1.5);
  iShowLoadedSVG(100, 200, &svg);
  ``` -->

### 🧩 Sprite Functions

Free sprite resources: [https://craftpix.net/freebies/](https://craftpix.net/freebies/)\\
Online sprite cutter: [https://ezgif.com/sprite-cutter](https://ezgif.com/sprite-cutter)

#### `void iInitSprite(Sprite *s)`

- **Description:** Initializes a sprite structure.
- **Parameters:**

  - `s`: Pointer to a `Sprite` structure.

- **Example:**
  ```cpp
  Sprite s;
  iInitSprite(&s); // Initialize sprite and ignore white color
  ```
- **Sprite Structure**
  ```cpp
  typedef struct
  {
      int x, y;
      int currentFrame;
      ....
  } Sprite;
  ```

#### `void iLoadFramesFromFolder(Image *frames, const char *folderPath)`

- **Description:** Loads frames from a folder containing multiple images.
- **Parameters:**

  - `frames`: Pointer to an array of `Image` structures.
  - `folderPath`: Path to the folder containing images.

- **Example:**
  ```cpp
  Image frames[10];
  iLoadFramesFromFolder(frames, "sprites/"); // Load images from a folder and ignore no color
  ```

#### `void iLoadFramesFromSheet(Image *frames, const char *filename, int rows, int cols)`

- **Description:** Loads frames from a sprite sheet.
- **Parameters:**

  - `frames`: Pointer to an array of `Image` structures.
  - `filename`: Path to the sprite sheet image.
  - `rows`: Number of rows in the sprite sheet.
  - `cols`: Number of columns in the sprite sheet.

- **Example:**
  ```cpp
  Image frames[16];
  iLoadFramesFromSheet(frames, "spritesheet.png", 4, 4); // Load images frames a sprite sheet with 4 rows and 4 columns
  ```

#### `void iChangeSpriteFrames(Sprite *s, const Image *frames, int totalFrames)`

- **Description:** Changes the frames of a sprite.
- **Parameters:**

  - `s`: Pointer to a `Sprite` structure.
  - `frames`: Array of `Image` structures representing the new frames.
  - `totalFrames`: Number of frames in the array.

- **Example:**
  ```cpp
  Image frames[10];
  iLoadFramesFromFolder(frames,"sprites/"); // Load images from a folder
  Sprite s;
  iInitSprite(&s); // Initialize sprite
  iChangeSpriteFrames(&s, frames, 4); // Change the frames of the sprite
  ```

#### `void iSetSpritePosition(Sprite* s, int x, int y)`

- **Description:** Sets the position of the sprite.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
  - `x`, `y`: New coordinates for the sprite.
- **Example:**
  ```cpp
  iSetSpritePosition(&s, 100, 200); // Set sprite position to (100, 200)
  ```

#### `void iShowSprite(Sprite* s)`

- **Description:** Displays the sprite on the screen.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.

#### `void iAnimateSprite(Sprite* s)`

- **Description:** Animates the sprite by cycling through its frames.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
- **Example:**
  ```cpp
  iAnimateSprite(&s); // Animate the sprite
  ```

#### `void iScaleSprite(Sprite* s, double scale)`

- **Description:** Scales the sprite by a specified factor.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
  - `scale`: Scaling factor (e.g., 2.0 for double size).

#### `void iResizeSprite(Sprite* s, int width, int height)`

- **Description:** Resizes the sprite to specified dimensions.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
  - `width`: New width of the sprite.
  - `height`: New height of the sprite.

#### `void iMirrorSprite(Sprite* s, MirrorState state)`

- **Description:** Mirrors the sprite either horizontally or vertically.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
  - `state`: `HORIZONTAL` or `VERTICAL`.

#### `void iRotateSprite(Sprite* s, double x, double y, double degree)`

- **Description:** Rotates the sprite around a point `(x, y)` by a specified angle in degrees.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.
  - `x`, `y`: Coordinates of the point to rotate around.
  - `degree`: Angle in degrees to rotate.
- **Example:**
  ```cpp
  iRotateSprite(&s, 100, 100, 45); // Rotate sprite around point (100, 100) by 45 degrees
  ```

#### `void iFreeSprite(Sprite* s)`

- **Description:** Frees the memory allocated for the sprite.
- **Parameters:**
  - `s`: Pointer to a `Sprite` structure.

#### `int iCheckCollision(Sprite* s1, Sprite* s2)`

- **Description:** Checks for pixel-level collision between two sprites. If the bounding box of two images do not overlap, this has a time complexity of `O(1)`. Otherwise, it has a time complexity of `O(wh)`, where `w` and `h` are the width and height of the overlapping area of the two images.

- **Parameters:**
  - `s1`: Pointer to the first `Sprite` structure.
  - `s2`: Pointer to the second `Sprite` structure.
- **Returns:** `1` if collision is detected, `0` otherwise.
- **Example:**
  ```cpp
  Sprite s1, s2;
  ....
  if (iCheckCollision(&s1, &s2)) {
      // Collision detected
  }
  ```

#### `int iGetVisiblePixelsCount(Sprite* s1)`

- **Description:** Counts the number of visible pixels in a sprite. This is useful for collision detection.
- **Parameters:**
  - `s1`: Pointer to the `Sprite` structure.
  - **Returns:** Number of visible pixels in the sprite.
- **Example:**
- ```cpp
  Sprite s1;
  ...
  int visiblePixels = iGetVisiblePixelsCount(&s1);
  ```

### 🧰 Miscellaneous

#### `void iEnterFullscreen()`

- **Description:** Enters fullscreen mode.
- **Example:**
  ```cpp
  iEnterFullscreen(); // Enter fullscreen mode
  ```

#### `void iLeaveFullscreen()`

- **Description:** Exits fullscreen mode and returns to windowed mode.
- **Example:**
- ```cpp
  iLeaveFullscreen(); // Exit fullscreen mode
  ```

---

<!-- ## ✨ Contributors

| [![Shahriar Nirjon](https://github.com/nirjon.png?size=100)](https://github.com/nirjon) | [![Mahir Labib Dihan](https://github.com/mahirlabibdihan.png?size=100)](https://github.com/mahirlabibdihan) | [![Anwarul Bashar Shuaib](https://github.com/shuaibw.png?size=100)](https://github.com/shuaibw) | [![Ashrafur Rahman Khan](https://github.com/risenfromashes.png?size=100)](https://github.com/risenfromashes) |
| :-------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------: |
|                                   **Shahriar Nirjon**                                   |                                            **Mahir Labib Dihan**                                            |                                    **Anwarul Bashar Shuaib**                                    |                                         **Md. Ashrafur Rahman Khan**                                         |

--- -->

## 📄 License

This library is for educational purposes and is typically used in academic or hobbyist OpenGL projects.

<!-- My contribution -->

## 🧠 My Contribution

- **Documentation:** Documented iGraphics with updated features gathered from various iGraphics projects mentioned in the acknowledgements.
- **Cross-Platform:** Added support for Linux. Previously, it was only supported on Windows.
- **Custom Font**: Added support for TrueType fonts using `freetype` library.
- **Rotation**: Added image and sprite rotation. The challenge in sprite rotation was that, collision detection should still work after rotation.
- **Image**: Using `stb_image` library, added support for loading images in various formats (BMP, PNG, JPG, GIF, etc). Previously, only BMP format was supported. Also, using `Nano SVG`, added support for loading SVG images.
- **Texture**: Used texture for image and sprite rendering, which allows for better performance and flexibility. Previously, images were rendered using `glDrawPixels`, which is less efficient. One major benefit is that, previously we couldn't draw images with negative `x` or `y` coordinates, but now we can draw images at any position on the screen. Also, rotation of images was possible because of this change.
- **Keyboard**: Added support for keyboard key release detection. Also, now, we can check if a key is pressed or not using `isKeyPressed` and `isSpecialKeyPressed` functions. This enables parallel key detection, which was not possible before.
- **Mouse**: Added support for mouse passive motion and mouse wheel scrolling. Also, now we can show or hide the mouse cursor using `iShowCursor` and `iHideCursor` functions.
- **Sprite**: Added functions to easily work with sprites, including loading frames from folders and sprite sheets (Previously, needed to use a online sprite cutter), animating sprites.
- **Image Wrap**: Now image wrapping is possible in all four directions (left, right, up, down) using `iWrapImage`. Previously, only in the right direction was possible.
- **Closing Window**: Added `iCloseWindow` function to close the current window. No such function was available previously. Had to use `exit(0)` to close the window, which is not a good practice.
- **Sound**: Added sound playback functionality using `SDL2` library. Now, we can play sounds, pause, resume, and stop them. Also, added volume control for sounds. Specially, parallel sound playback is now possible, which was not possible before. Previously, windows specific `PlaySound` function was used, which was not cross-platform.
- **Timer**: Used `glutTimerFunc` for timer functionality. Previously, windows specific `SetTimer` function was used, which was not cross-platform.
- **Scaling**: Added support for scaling anything (drawings, images, text) using `iScale` and `iUnscale` functions.
- **Callbacks**: Made iGraphics function callbacks (e.g., `iDraw`, `iMouseClick`, `iKeyPress`) optional, so that users can choose to implement only the functions they need.
- **Naming**: Renamed some functions and parameters for better clarity and consistency. For example, `iOpenWindow` instead of `iInitialize`, `iMouseDrag` instead of `iMouseMove`, `iMouseClick` instead of `iMouse`, `iShowImage` instead of `iShowBMP`, etc. This makes the API more intuitive and easier to use.

## 🙏 Acknowledgements

- [Shahriar Nirjon](https://github.com/nirjon) - Original iGraphics library
- [Ashrafur Rahman Khan](https://github.com/risenfromashes) - Linux Support, Freeglut, SDL2 sound engine, Transparent Color, Mouse passive motion and Mouse wheel ([repository](https://github.com/risenfromashes/catch-the-egg))
- [Anwarul Bashar Shuaib](https://github.com/shuaibw) - Image cache, resize, mirror, wrap, and pixel-perfect collision detection functionality ([repository](https://github.com/shuaibw/iGraphics-extended/))
- [Wasif Jalal](https://github.com/wjalal) - SDL2 sound engine, Game Mode ([repository](https://github.com/wjalal/1-1_term_project_igraphics_dxball))

<!-- ## 🙏 Acknowledgements


- [Extended iGraphics by Ash](https://github.com/risenfromashes/Curves/) - Implementation of cross-platform iGraphics library with additional features.
- [irrKlang](https://github.com/jonas2602/irrKlang) - The sound engine used for sound playback.
- [freeglut](https://freeglut.sourceforge.net/) - The OpenGL Utility Toolkit. -->

<!-- Resources -->

## 📚 Libraries

- [SDL2](https://www.libsdl.org/): v2.0.12
  - [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/): v2.0.4
- [Freetype](https://gnuwin32.sourceforge.net/packages/freetype.htm): v2.3.5
  - [zlib](https://gnuwin32.sourceforge.net/packages/zlib.htm): v1.2.3
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h): v2.30
  - [stb_image_resize](https://github.com/nothings/stb/blob/master/stb_image_resize_test/old_image_resize.h): v0.96
- [Nano SVG](https://github.com/memononen/nanosvg)
