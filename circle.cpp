#include <graphics.h>
#include <conio.h> // for getch()

int main() {
    // Initialize the graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // Update the path if needed

    // Set the color for the circle
    setcolor(WHITE);

    // Draw a circle at (x=250, y=250) with a radius of 100
    circle(250, 250, 100);

    // Keep the graphics window open until a key is pressed
    getch();

    // Close the graphics window
    closegraph();

    return 0;
}
