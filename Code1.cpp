#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <string>

#define PI 3.14159265

// Function to rotate a point (x, y) around the origin by a given angle in degrees
void rotate_point(int &x, int &y, float angle) {
    float radian = angle * PI / 180.0;  // Convert angle to radians
    int temp_x = x;
    x = static_cast<int>(x * cos(radian) - y * sin(radian));
    y = static_cast<int>(temp_x * sin(radian) + y * cos(radian));
}

// Function to draw the polygon and dotted lines
void draw_polygon(int n_sides, int radius, int center_x, int center_y, int points[][2], int rotation_offset = 0) {
    float angle_step = 360.0 / n_sides;
    int colors[] = {WHITE, RED, GREEN, BLUE}; // Colors for the dotted lines

    // Draw the polygon and store the vertices
    for (int i = 0; i < n_sides; i++) {
        float angle = (i * angle_step + rotation_offset) * PI / 180.0;
        points[i][0] = center_x + static_cast<int>(radius * cos(angle));
        points[i][1] = center_y + static_cast<int>(radius * sin(angle));
    }

    // Draw the edges of the polygon
    for (int i = 0; i < n_sides; i++) {
        line(points[i][0], points[i][1], points[(i + 1) % n_sides][0], points[(i + 1) % n_sides][1]);
    }

    // Draw the center to vertex lines with alternating colors
    int color_index = 0;
    for (int i = 0; i < n_sides; i++) {
        setcolor(colors[color_index % 4]);
        // Draw a dotted line from the center to the vertex
        for (int j = 0; j < 10; j++) {
            // Creating the dotted effect by drawing short lines
            int x1 = center_x + (points[i][0] - center_x) * j / 10;
            int y1 = center_y + (points[i][1] - center_y) * j / 10;
            int x2 = center_x + (points[i][0] - center_x) * (j + 1) / 10;
            int y2 = center_y + (points[i][1] - center_y) * (j + 1) / 10;
            line(x1, y1, x2, y2);
        }
        color_index++;
    }

    // Number the vertices at the current positions after rotation
    for (int i = 0; i < n_sides; i++) {
        std::string vertex_number = std::to_string(i + 1);
        outtextxy(points[i][0] + 10, points[i][1] + 10, const_cast<char*>(vertex_number.c_str()));
    }
}

// Function to rotate all points by a given angle
void rotate_polygon(int n_sides, int points[][2], int center_x, int center_y, float angle) {
    for (int i = 0; i < n_sides; i++) {
        int x = points[i][0] - center_x;
        int y = points[i][1] - center_y;
        rotate_point(x, y, angle);
        points[i][0] = x + center_x;
        points[i][1] = y + center_y;
    }
}

// Main function to run the program
int main() {
    int n_sides = 7; // Number of sides of the polygon (can be odd)
    int radius = 100; // Radius of the polygon
    int center_x = 320, center_y = 240; // Center of the screen
    int points[n_sides][2]; // Array to store the points of the polygon
    int rotation_offset = 0; // Angle for rotation (initially no rotation)

    // Initialize the graphics driver and mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Draw the polygon and number the vertices
    draw_polygon(n_sides, radius, center_x, center_y, points);

    // Wait for a mouse click to rotate the polygon
    while (!kbhit()) {
        if (mousex() >= 0 && mousey() >= 0) {
            // Wait for the user to click
            if (ismouseclick(WM_LBUTTONDOWN)) {
                cleardevice(); // Clear the screen
                
                // Rotate the polygon by 360/n degrees
                rotation_offset += 360 / n_sides;
                if (rotation_offset >= 360) rotation_offset -= 360;

                // Rotate and redraw the polygon after each click
                rotate_polygon(n_sides, points, center_x, center_y, 360.0 / n_sides);
                draw_polygon(n_sides, radius, center_x, center_y, points, rotation_offset);

                // Reset the mouse click
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }

    // Close the graphics mode
    closegraph();
    return 0;
}
