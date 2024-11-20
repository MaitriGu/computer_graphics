#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <string>

#define PI 3.14159265

using namespace std;

void rotate_point(int &x, int &y, float angle) {
    float radian = angle * PI / 180.0;
    int temp_x = x;
    x = static_cast<int>(x * cos(radian) - y * sin(radian));
    y = static_cast<int>(temp_x * sin(radian) + y * cos(radian));
}

void draw_white_black_dashed_line(int x1, int y1, int x2, int y2) {
    int dashLength = 20;  // Dash length
    int gapLength = 30;   // Gap length
    int dx = x2 - x1;
    int dy = y2 - y1;
    float dist = sqrt(dx * dx + dy * dy);
    int numDashes = dist / (dashLength + gapLength);
    
    for (int i = 0; i < numDashes; i++) {
        float t1 = (float)i / numDashes;
        float t2 = (float)(i + 1) / numDashes;
        int xStart = static_cast<int>(x1 + t1 * dx);
        int yStart = static_cast<int>(y1 + t1 * dy);
        int xEnd = static_cast<int>(x1 + t2 * dx);
        int yEnd = static_cast<int>(y1 + t2 * dy);

        // Alternate between white and black dashes
        if (i % 2 == 0) {
            setcolor(WHITE);  // White dash
        } else {
            setcolor(BLACK);  // Black (gap) dash
        }
        line(xStart, yStart, xEnd, yEnd);
    }
}

void draw_multicolored_dashed_line(int x1, int y1, int x2, int y2) {
    int dashLength = 10;  // Dash length
    int gapLength = 30;   // Gap length
    int dx = x2 - x1;
    int dy = y2 - y1;
    float dist = sqrt(dx * dx + dy * dy);
    int numDashes = dist / (dashLength + gapLength);
    int colors[] = {RED, GREEN, BLUE};

    for (int i = 0; i < numDashes; i++) {
        float t1 = (float)i / numDashes;
        float t2 = (float)(i + 1) / numDashes;
        int xStart = static_cast<int>(x1 + t1 * dx);
        int yStart = static_cast<int>(y1 + t1 * dy);
        int xEnd = static_cast<int>(x1 + t2 * dx);
        int yEnd = static_cast<int>(y1 + t2 * dy);

        setcolor(colors[i % 3]);
        line(xStart, yStart, xEnd, yEnd);
    }
}

void draw_polygon(int n_sides, int radius, int center_x, int center_y, int points[][2], int rotation_offset = 0) {
    float angle_step = 360.0 / n_sides;

    for (int i = 0; i < n_sides; i++) {
        float angle = (i * angle_step + rotation_offset) * PI / 180.0;
        points[i][0] = center_x + static_cast<int>(radius * cos(angle));
        points[i][1] = center_y + static_cast<int>(radius * sin(angle));
    }

    for (int i = 0; i < n_sides; i++) {
        line(points[i][0], points[i][1], points[(i + 1) % n_sides][0], points[(i + 1) % n_sides][1]);
    }

    for (int i = 0; i < n_sides; i++) {
        if (i % 2 == 0) {
            draw_white_black_dashed_line(center_x, center_y, points[i][0], points[i][1]);
        } else {
            draw_multicolored_dashed_line(center_x, center_y, points[i][0], points[i][1]);
        }

        string vertex_number = to_string(i + 1);
        setcolor(WHITE);
        outtextxy(points[i][0] + 10, points[i][1] + 10, const_cast<char*>(vertex_number.c_str()));
    }
}

void rotate_polygon(int n_sides, int points[][2], int center_x, int center_y, float angle) {
    for (int i = 0; i < n_sides; i++) {
        int x = points[i][0] - center_x;
        int y = points[i][1] - center_y;
        rotate_point(x, y, angle);
        points[i][0] = x + center_x;
        points[i][1] = y + center_y;
    }
}

int main() {
    int n_sides;
    cout << "Enter number of sides for the polygon (n): ";
    cin >> n_sides;

    int radius = 200;  // Increased radius for better visibility
    int center_x = 320, center_y = 240;
    int points[n_sides][2];
    int rotation_offset = 0;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    draw_polygon(n_sides, radius, center_x, center_y, points);

    while (!kbhit()) {
        if (mousex() >= 0 && mousey() >= 0) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                cleardevice();
                rotation_offset += 360 / n_sides;
                if (rotation_offset >= 360) rotation_offset -= 360;
                rotate_polygon(n_sides, points, center_x, center_y, 360.0 / n_sides);
                draw_polygon(n_sides, radius, center_x, center_y, points, rotation_offset);
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }

    closegraph();
    return 0;
}
