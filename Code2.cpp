#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define MAX_POLY 50

int centerX, centerY, radius, n;  // n-sided polygon, radius of circumscribed circle

// Function to draw the polygon with n sides
void drawPolygon(int centerX, int centerY, int radius, int n) {
    int x[MAX_POLY], y[MAX_POLY];

    // Calculate the vertices of the polygon
    for (int i = 0; i < n; i++) {
        x[i] = centerX + radius * cos(2 * M_PI * i / n);
        y[i] = centerY + radius * sin(2 * M_PI * i / n);
    }

    // Draw the polygon by connecting vertices
    setcolor(WHITE);
    for (int i = 0; i < n - 1; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    line(x[n - 1], y[n - 1], x[0], y[0]);  // Closing the polygon
}

// Function to divide the polygon into n equal parts and color each differently
void colorParts(int centerX, int centerY, int radius, int n) {
    int x[MAX_POLY], y[MAX_POLY];

    // Calculate the vertices of the polygon
    for (int i = 0; i < n; i++) {
        x[i] = centerX + radius * cos(2 * M_PI * i / n);
        y[i] = centerY + radius * sin(2 * M_PI * i / n);
    }

    // Color each part differently by filling each sector with a different color
    for (int i = 0; i < n; i++) {
        // Generate a unique color for each part
        int color = (i % 15) + 1; // Colors range from 1 to 15

        setfillstyle(SOLID_FILL, color); // Set the fill color

        // Draw a triangle from the center to two consecutive vertices
        int next = (i + 1) % n; // The next vertex, looping around
        int polyX[] = {centerX, x[i], x[next]};
        int polyY[] = {centerY, y[i], y[next]};

        // Fill the triangle (sector) with color
        floodfill((polyX[0] + polyX[1] + polyX[2]) / 3, (polyY[0] + polyY[1] + polyY[2]) / 3, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Initialize the center and radius for the polygon
    centerX = getmaxx() / 2;
    centerY = getmaxy() / 2;
    radius = 150;  // Radius of the circumscribed circle for the polygon

    // Take input n for the number of sides
    std::cout << "Enter the number of sides (n): ";
    std::cin >> n;

    // Draw the polygon and color the parts
    drawPolygon(centerX, centerY, radius, n);
    colorParts(centerX, centerY, radius, n);

    getch();
    closegraph();
    return 0;
}
