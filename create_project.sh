#!/bin/bash

# Check if filename argument is provided
if [ $# -eq 0 ]; then
    echo "📋 Usage: ./create_project.sh <filename>"
    echo "💡 Example: ./create_project.sh MyGame"
    echo ""
    echo "🎯 This will create MyGame.cpp with iGraphics starter code"
    exit 1
fi

filename="$1"

echo "🚀 Creating project file for: $filename"

# Remove .cpp extension if provided
if [[ "$filename" == *.cpp ]]; then
    filename="${filename%.cpp}"
fi

output_file="${filename}.cpp"

echo "📁 Output file will be: $output_file"

# Check if file already exists
if [ -f "$output_file" ]; then
    echo "⚠️  Error: File \"$output_file\" already exists!"
    echo "🔄 Overwriting existing file..."
fi

echo "✨ Creating \"$output_file\"..."

# Create the skeleton C++ file
cat > "$output_file" << 'EOF'
#include "iGraphics.h"

// Global variables
int screenWidth = 800;
int screenHeight = 600;

// Game state variables
// Add your variables here

/*
 * iDraw() is called repeatedly by the system.
 * Place your drawing code here.
 */
void iDraw()
{
    // Clear the screen
    iClear();

    // Set drawing color (Red, Green, Blue)
    iSetColor(255, 255, 255);

    // Draw your graphics here
    iText(50, screenHeight - 50, "Hello, iGraphics!");
    iText(50, screenHeight - 80, "Press 'q' to quit, 'f' for fullscreen");

    // Example: Draw a circle
    iSetColor(255, 0, 0);
    iFilledCircle(screenWidth/2, screenHeight/2, 50);
}

/*
 * iMouseClick() is called when mouse is clicked.
 * button: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
 * state: GLUT_DOWN, GLUT_UP
 * mx, my: mouse coordinates
 */
void iMouseClick(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Left mouse button pressed
        printf("Mouse clicked at: %d, %d\n", mx, my);
    }
}

/*
 * iMouseMove() is called when mouse moves.
 * mx, my: mouse coordinates
 */
void iMouseMove(int mx, int my)
{
    // Mouse move code here
}

/*
 * iKeyPress() is called when a regular key is pressed.
 * key: ASCII value of the key
 */
void iKeyPress(unsigned char key)
{
    switch (key)
    {
    case 'q':
    case 'Q':
        iCloseWindow();
        break;
    case 'f':
    case 'F':
        iToggleFullscreen();
        break;
    case ' ':
        // Space key pressed
        break;
    default:
        printf("Key pressed: %c (ASCII: %d)\n", key, key);
        break;
    }
}

/*
 * iSpecialKeyPress() is called when special keys are pressed.
 * Available keys: GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT,
 * GLUT_KEY_F1-F12, GLUT_KEY_HOME, GLUT_KEY_END, etc.
 */
void iSpecialKeyPress(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        // Up arrow pressed
        break;
    case GLUT_KEY_DOWN:
        // Down arrow pressed
        break;
    case GLUT_KEY_LEFT:
        // Left arrow pressed
        break;
    case GLUT_KEY_RIGHT:
        // Right arrow pressed
        break;
    case GLUT_KEY_END:
        iCloseWindow();
        break;
    default:
        break;
    }
}

/*
 * Animation timer function.
 * This function is called repeatedly for animations.
 * dt: time difference in milliseconds since last call
 */
void iAnimation()
{
    // Animation code here
    // For example: update positions, change colors, etc.
}

/*
 * Main function - Entry point of the program
 */
int main(int argc, char *argv[])
{
    // Initialize any resources here
    // For example: load images, sounds, etc.

    // Set up animation timer (optional)
    // iSetTimer(16, iAnimation); // ~60 FPS

    // Open the graphics window
    iOpenWindow(screenWidth, screenHeight, "EOF

# Add the filename to the window title
echo "    iOpenWindow(screenWidth, screenHeight, \"$filename\");" >> "$output_file"

# Add the closing part
cat >> "$output_file" << 'EOF'

    return 0;
}
EOF

echo ""
echo "✅ Successfully created \"$output_file\"!"
echo ""
echo "🔨 To compile and run: ./runner.sh $output_file"
echo ""
echo "🎉 Happy coding with iGraphics!"
echo ""
