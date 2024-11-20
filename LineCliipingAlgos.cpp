#include <graphics.h>
#include <iostream>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int xMin = 100, yMin = 100, xMax = 400, yMax = 400;

int computeOutCode(int x, int y) {
    int code = 0;
    if (x < xMin) code |= LEFT;
    else if (x > xMax) code |= RIGHT;
    if (y < yMin) code |= BOTTOM;
    else if (y > yMax) code |= TOP;
    return code;
}

void cohenSutherlandLineClip(int x0, int y0, int x1, int y1) {
    int outcode0 = computeOutCode(x0, y0);
    int outcode1 = computeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            break;
        } else {
            int x, y;
            int outcodeOut = outcode0 ? outcode0 : outcode1;
            if (outcodeOut & TOP) {
                x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
                y = yMax;
            } else if (outcodeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
                y = yMin;
            } else if (outcodeOut & RIGHT) {
                y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
                x = xMax;
            } else if (outcodeOut & LEFT) {
                y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
                x = xMin;
            }
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    }

    if (accept) {
        setcolor(GREEN);
        line(x0, y0, x1, y1);
    } else {
        setcolor(RED);
        line(x0, y0, x1, y1);
    }
}

void liangBarskyLineClip(int x0, int y0, int x1, int y1) {
    float p[4], q[4];
    float t0 = 0.0, t1 = 1.0;
    p[0] = x1 - x0; q[0] = x0 - xMin;
    p[1] = -(x1 - x0); q[1] = xMax - x0;
    p[2] = y1 - y0; q[2] = y0 - yMin;
    p[3] = -(y1 - y0); q[3] = yMax - y0;

    for (int i = 0; i < 4; i++) {
        float r = q[i] / p[i];
        if (p[i] < 0) {
            if (r > t1) return; 
            else if (r > t0) t0 = r;
        } else if (p[i] > 0) {
            if (r < t0) return;
            else if (r < t1) t1 = r;
        } else if (q[i] < 0) return;
    }

    setcolor(GREEN);
    line(x0 + t0 * p[0], y0 + t0 * p[2], x0 + t1 * p[0], y0 + t1 * p[2]);
}

void drawClippingWindow() {
    setcolor(WHITE);
    rectangle(xMin, yMin, xMax, yMax);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawClippingWindow();
    int x0, y0, x1, y1;

    cout << "Click on the screen to define the line endpoints." << endl;
    cout << "Select the clipping algorithm: \n";
    cout << "1. Cohen-Sutherland Line Clipping\n";
    cout << "2. Liang-Barsky Line Clipping\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    // Wait for the first mouse click for the first point
    while (!ismouseclick(WM_LBUTTONDOWN)) delay(1);
    getmouseclick(WM_LBUTTONDOWN, x0, y0);

    // Wait for the second mouse click for the second point
    while (!ismouseclick(WM_LBUTTONDOWN)) delay(1);
    getmouseclick(WM_LBUTTONDOWN, x1, y1);

    setcolor(RED);
    line(x0, y0, x1, y1);

    if (choice == 1) {
        cohenSutherlandLineClip(x0, y0, x1, y1);
    } else if (choice == 2) {
        liangBarskyLineClip(x0, y0, x1, y1);
    }

    getch();
    closegraph();
    return 0;
}
