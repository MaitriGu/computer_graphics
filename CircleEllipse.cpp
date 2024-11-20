#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

enum Shape { CIRCLE, ELLIPSE };

Shape selectedShape = CIRCLE;
int color = WHITE;

void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);
        x++;

        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void midpointEllipse(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2;
    int x = 0, y = ry;
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);

        if (d1 < 0) {
            x++;
            dx += 2 * ry * ry;
            d1 += dx + (ry * ry);
        } else {
            x++;
            y--;
            dx += 2 * ry * ry;
            dy -= 2 * rx * rx;
            d1 += dx - dy + (ry * ry);
        }
    }

    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    while (y >= 0) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);

        if (d2 > 0) {
            y--;
            dy -= 2 * rx * rx;
            d2 += (rx * rx) - dy;
        } else {
            y--;
            x++;
            dx += 2 * ry * ry;
            dy -= 2 * rx * rx;
            d2 += dx - dy + (rx * rx);
        }
    }
}

void showMenu() {
    cout << "Choose a shape to draw:\n";
    cout << "1. Midpoint Circle\n2. Midpoint Ellipse\n";
    int choice;
    cin >> choice;
    selectedShape = static_cast<Shape>(choice - 1);
    cout << "Choose a color (0-15):\n";
    cin >> color;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    showMenu();
    int xc, yc, radius, rx, ry;

    cout << "Click the center point on the screen.\n";
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, xc, yc);
    cout << "Center: (" << xc << ", " << yc << ")\n";

    if (selectedShape == CIRCLE) {
        cout << "Click a point to define the radius.\n";
        int x2, y2;
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, x2, y2);
        radius = sqrt(pow(x2 - xc, 2) + pow(y2 - yc, 2));
        midpointCircle(xc, yc, radius);
    } else {
        cout << "Click a point to define the semi-major axis.\n";
        int x2, y2;
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, x2, y2);
        rx = abs(x2 - xc);
        
        cout << "Click a point to define the semi-minor axis.\n";
        int x3, y3;
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, x3, y3);
        ry = abs(y3 - yc);
        
        midpointEllipse(xc, yc, rx, ry);
    }

    getch();
    closegraph();
    return 0;
}
