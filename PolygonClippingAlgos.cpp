#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<iostream>

#define MAX_POLY 20

int x_min, y_min, x_max, y_max;

int inside(int x, int y, int edge) {
    switch (edge) {
        case 0: return x >= x_min;
        case 1: return x <= x_max;
        case 2: return y >= y_min;
        case 3: return y <= y_max;
    }
    return 0;
}

void intersect(int x1, int y1, int x2, int y2, int edge, int *x, int *y) {
    float m = (float)(y2 - y1) / (x2 - x1);

    switch (edge) {
        case 0:
            *x = x_min;
            *y = y1 + m * (x_min - x1);
            break;
        case 1:
            *x = x_max;
            *y = y1 + m * (x_max - x1);
            break;
        case 2:
            *y = y_min;
            *x = x1 + (y_min - y1) / m;
            break;
        case 3:
            *y = y_max;
            *x = x1 + (y_max - y1) / m;
            break;
    }
}

void sutherlandHodgman(int *polyX, int *polyY, int n, int *clippedX, int *clippedY, int *clippedCount) {
    int newPolyX[MAX_POLY], newPolyY[MAX_POLY];
    int newPolyCount = n;

    for (int edge = 0; edge < 4; edge++) {
        int prevX = polyX[newPolyCount - 1];
        int prevY = polyY[newPolyCount - 1];
        int newCount = 0;

        for (int i = 0; i < newPolyCount; i++) {
            int currX = polyX[i];
            int currY = polyY[i];

            if (inside(currX, currY, edge)) {
                if (!inside(prevX, prevY, edge)) {
                    intersect(prevX, prevY, currX, currY, edge, &newPolyX[newCount], &newPolyY[newCount]);
                    newCount++;
                }
                newPolyX[newCount] = currX;
                newPolyY[newCount] = currY;
                newCount++;
            } else if (inside(prevX, prevY, edge)) {
                intersect(prevX, prevY, currX, currY, edge, &newPolyX[newCount], &newPolyY[newCount]);
                newCount++;
            }

            prevX = currX;
            prevY = currY;
        }

        newPolyCount = newCount;

        for (int i = 0; i < newPolyCount; i++) {
            polyX[i] = newPolyX[i];
            polyY[i] = newPolyY[i];
        }
    }

    *clippedCount = newPolyCount;
    for (int i = 0; i < newPolyCount; i++) {
        clippedX[i] = newPolyX[i];
        clippedY[i] = newPolyY[i];
    }
}

void drawPolygon(int *x, int *y, int n) {
    for (int i = 0; i < n - 1; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    line(x[n - 1], y[n - 1], x[0], y[0]);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    x_min = 150;
    y_min = 100;
    x_max = 450;
    y_max = 350;

    setcolor(GREEN);
    rectangle(x_min, y_min, x_max, y_max);

    int polyX[MAX_POLY], polyY[MAX_POLY];
    int clippedX[MAX_POLY], clippedY[MAX_POLY];
    int vertexCount = 0;

    printf("Click to draw a polygon. Press 'Enter' when done.\n");

    while (1) {
        if (vertexCount < MAX_POLY) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                int mx, my;
                getmouseclick(WM_LBUTTONDOWN, mx, my);
                polyX[vertexCount] = mx;
                polyY[vertexCount] = my;
                vertexCount++;
                setcolor(WHITE);
                fillellipse(mx, my, 4,3);
            }
        } else {
            break;
        }

        if (kbhit() && getch() == 13) { // enter
            break;
        }
    }

    setcolor(WHITE);
    drawPolygon(polyX, polyY, vertexCount);

    int clippedCount = 0;
    sutherlandHodgman(polyX, polyY, vertexCount, clippedX, clippedY, &clippedCount);

    setcolor(YELLOW);
    drawPolygon(clippedX, clippedY, clippedCount);

    getch();
    closegraph();
    return 0;
}