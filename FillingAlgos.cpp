#include <graphics.h>
#include <iostream>
#include <vector>

using namespace std;

void boundaryFill(int x, int y, int fillColor, int boundaryColor) {
    int currentColor = getpixel(x, y);
    if (currentColor != boundaryColor && currentColor != fillColor) {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

void floodFill(int x, int y, int fillColor, int backgroundColor) {
    int currentColor = getpixel(x, y);
    if (currentColor == backgroundColor && currentColor != fillColor) {
        putpixel(x, y, fillColor);
        floodFill(x + 1, y, fillColor, backgroundColor);
        floodFill(x - 1, y, fillColor, backgroundColor);
        floodFill(x, y + 1, fillColor, backgroundColor);
        floodFill(x, y - 1, fillColor, backgroundColor);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    vector<int> points;
    int x, y;

    cout << "Click to define the vertices of the polygon. Right-click to stop." << endl;

    while (true) {
        while (!ismouseclick(WM_LBUTTONDOWN) && !ismouseclick(WM_RBUTTONDOWN)) {}

        if (ismouseclick(WM_RBUTTONDOWN)) {
            break;  // Stop taking points when the right mouse button is clicked
        }

        getmouseclick(WM_LBUTTONDOWN, x, y);
        points.push_back(x);
        points.push_back(y);
        putpixel(x, y, WHITE);

        if (points.size() > 2) {
            line(points[points.size() - 4], points[points.size() - 3], x, y);
        }
    }

    if (points.size() >= 4) {
        line(points[0], points[1], points[points.size() - 2], points[points.size() - 1]);
    }

    int fillColor = RED;
    int boundaryColor = WHITE;

    cout << "Click inside the polygon to fill it." << endl;
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x, y);

    // Choose the filling algorithm (boundary fill or flood fill)
    int choice;
    cout << "Choose fill algorithm: 1 for Boundary Fill, 2 for Flood Fill: ";
    cin >> choice;

    if (choice == 1) {
        boundaryFill(x, y, fillColor, boundaryColor);
    } else if (choice == 2) {
        int backgroundColor = getpixel(x, y);
        floodFill(x, y, fillColor, backgroundColor);
    }

    getch();
    closegraph();
    return 0;
}
