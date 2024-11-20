#include <graphics.h>
#include <iostream>

using namespace std;

enum LinePattern { SOLID, DASHED, DOTTED, PARALLEL };
enum LineAlgorithm { SIMPLE_DDA, SYMMETRIC_DDA, BRESENHAM, MIDPOINT };

LinePattern selectedPattern = SOLID;
LineAlgorithm selectedAlgorithm = SIMPLE_DDA;
int color = WHITE;

void simpleDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xIncrement = dx / (float)steps, yIncrement = dy / (float)steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, color);
        x += xIncrement;
        y += yIncrement;
    }
}

void symmetricDDA(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int steps = max(dx, dy);
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, color);
        x += (dx / (float)steps) * ((x2 - x1) < 0 ? -1 : 1);
        y += (dy / (float)steps) * ((y2 - y1) < 0 ? -1 : 1);
    }
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int x = x1, y = y1;
    int xEnd = x2;
    int xStep = (x2 > x1) ? 1 : -1;
    int yStep = (y2 > y1) ? 1 : -1;

    putpixel(x, y, color);
    while (x != xEnd) {
        x += xStep;
        if (p < 0) {
            p += 2 * dy;
        } else {
            y += yStep;
            p += 2 * (dy - dx);
        }
        putpixel(x, y, color);
    }
}

void midpointLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int d = dy - (dx / 2);
    int x = x1, y = y1;
    int xEnd = x2;
    int yStep = (y2 > y1) ? 1 : -1;

    putpixel(x, y, color);
    while (x != xEnd) {
        x++;
        if (d < 0) {
            d += dy;
        } else {
            y += yStep;
            d += (dy - dx);
        }
        putpixel(x, y, color);
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    switch (selectedAlgorithm) {
        case SIMPLE_DDA: simpleDDA(x1, y1, x2, y2); break;
        case SYMMETRIC_DDA: symmetricDDA(x1, y1, x2, y2); break;
        case BRESENHAM: bresenham(x1, y1, x2, y2); break;
        case MIDPOINT: midpointLine(x1, y1, x2, y2); break;
    }
}

void showMenu() {
    cout << "Choose a line drawing algorithm:\n";
    cout << "1. Simple DDA\n2. Symmetric DDA\n3. Bresenham\n4. Midpoint\n";
    int choice;
    cin >> choice;
    selectedAlgorithm = static_cast<LineAlgorithm>(choice - 1);
    cout << "Choose a color (0-15):\n";
    cin >> color;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    showMenu();
    int x1, y1, x2, y2;

    cout << "Click two points on the screen to draw a line.\n";
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x1, y1);
    cout << "First point: (" << x1 << ", " << y1 << ")\n";

    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x2, y2);
    cout << "Second point: (" << x2 << ", " << y2 << ")\n";

    drawLine(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
