# iGraphics With Extended Features

This is an extended version of the iGraphics library with multiple image formats support and some additional features. New features will be added incrementally upon request. Original author of iGraphics is S. M. Shahriar Nirjon.

## Additional Features
- Support for multiple image formats (BMP, PNG, JPG, GIF) with the help of the stb_image library.
```
void iShowIMG(int x, int y, const char *fileName);
```
- Support for image resize.
```
void iShowIMGWithResize(int x, int y, int w, int h, const char *fileName);
```

## How to Use
- Include the iGraphics.h header file in your project.
- Change line 11 in runner.bat to the path of MinGW directory in your system.
- Run `runner.bat your_file_name.c` to compile and run your project.
- Executable will be created in the `exec` directory.