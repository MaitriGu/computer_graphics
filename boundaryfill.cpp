#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define MAX_VERTICES 100

void drawPolygon(int *x, int *y, int n) {
    for (int i = 0; i < n; i++) {
        line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }
}

void boundaryFill(int x, int y, int fillColor, int boundaryColor) {
    int current = getpixel(x, y);
    if (current != fillColor && current != boundaryColor) {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x[MAX_VERTICES], y[MAX_VERTICES];
    int vertexCount = 0;

    cout << "Click to draw a polygon. Press 'Enter' when done." << endl;

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            x[vertexCount] = mx;
            y[vertexCount] = my;
            vertexCount++;
            setcolor(WHITE);
            fillellipse(mx, my, 3, 3); // Marking points visually
        }
        if (kbhit() && getch() == 13) {
            break; // Enter key pressed
        }
    }

    drawPolygon(x, y, vertexCount);

    int fillX = (x[0] + x[vertexCount / 2]) / 2;
    int fillY = (y[0] + y[vertexCount / 2]) / 2;

    boundaryFill(fillX, fillY, YELLOW, WHITE);

    cout << "Press any key to exit..." << endl;
    getch();
    closegraph();
    return 0;
}

