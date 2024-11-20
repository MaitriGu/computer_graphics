#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define MAX_POLY 20

int polyX[MAX_POLY], polyY[MAX_POLY];
int transformedX[MAX_POLY], transformedY[MAX_POLY];
int vertexCount = 0;

void drawPolygon(int *x, int *y, int n, int color) {
    setcolor(color);
    for (int i = 0; i < n - 1; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    line(x[n - 1], y[n - 1], x[0], y[0]);
}

// Translation transformation
void translate(int *x, int *y, int n, int tx, int ty) {
    for (int i = 0; i < n; i++) {
        x[i] += tx;
        y[i] += ty;
    }
}

// Scaling transformation
void scale(int *x, int *y, int n, float sx, float sy) {
    for (int i = 0; i < n; i++) {
        x[i] = (int)(x[i] * sx);
        y[i] = (int)(y[i] * sy);
    }
}

// Rotation transformation
void rotate(int *x, int *y, int n, float angle) {
    float radian = angle * M_PI / 180.0;
    for (int i = 0; i < n; i++) {
        int newX = (int)(x[i] * cos(radian) - y[i] * sin(radian));
        int newY = (int)(x[i] * sin(radian) + y[i] * cos(radian));
        x[i] = newX;
        y[i] = newY;
    }
}

// Shearing transformation
void shear(int *x, int *y, int n, float shx, float shy) {
    for (int i = 0; i < n; i++) {
        x[i] = (int)(x[i] + y[i] * shx);
        y[i] = (int)(y[i] + x[i] * shy);
    }
}

// Reflection transformation (about the X-axis, Y-axis, or Y = X)
void reflect(int *x, int *y, int n, int choice) {
    for (int i = 0; i < n; i++) {
        switch (choice) {
            case 1: // Reflection about X-axis
                y[i] = -y[i];
                break;
            case 2: // Reflection about Y-axis
                x[i] = -x[i];
                break;
            case 3: // Reflection about Y = X line
                std::swap(x[i], y[i]);
                break;
            default:
                printf("Invalid reflection choice.\n");
                break;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    printf("Click to draw a polygon. Press 'Enter' when done.\n");

    // Draw the polygon using mouse clicks
    while (1) {
        if (vertexCount < MAX_POLY) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                int mx, my;
                getmouseclick(WM_LBUTTONDOWN, mx, my);
                polyX[vertexCount] = mx;
                polyY[vertexCount] = my;
                vertexCount++;
                setcolor(WHITE);
                fillellipse(mx, my, 4, 3);
            }
        } else {
            break;
        }

        if (kbhit() && getch() == 13) { // enter
            break;
        }
    }

    setcolor(WHITE);
    drawPolygon(polyX, polyY, vertexCount, WHITE); // Draw the original polygon

    printf("Enter the transformation type (1: Translation, 2: Scaling, 3: Rotation, 4: Shearing, 5: Reflection): ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            // Translation
            int tx, ty;
            printf("Enter translation values (tx, ty): ");
            scanf("%d %d", &tx, &ty);
            for (int i = 0; i < vertexCount; i++) {
                transformedX[i] = polyX[i];
                transformedY[i] = polyY[i];
            }
            translate(transformedX, transformedY, vertexCount, tx, ty);
            setcolor(GREEN);
            drawPolygon(transformedX, transformedY, vertexCount, GREEN);
            break;
        }
        case 2: {
            // Scaling
            float sx, sy;
            printf("Enter scaling factors (sx, sy): ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < vertexCount; i++) {
                transformedX[i] = polyX[i];
                transformedY[i] = polyY[i];
            }
            scale(transformedX, transformedY, vertexCount, sx, sy);
            setcolor(YELLOW);
            drawPolygon(transformedX, transformedY, vertexCount, YELLOW);
            break;
        }
        case 3: {
            // Rotation
            float angle;
            printf("Enter rotation angle: ");
            scanf("%f", &angle);
            for (int i = 0; i < vertexCount; i++) {
                transformedX[i] = polyX[i];
                transformedY[i] = polyY[i];
            }
            rotate(transformedX, transformedY, vertexCount, angle);
            setcolor(RED);
            drawPolygon(transformedX, transformedY, vertexCount, RED);
            break;
        }
        case 4: {
            // Shearing
            float shx, shy;
            printf("Enter shearing factors (shx, shy): ");
            scanf("%f %f", &shx, &shy);
            for (int i = 0; i < vertexCount; i++) {
                transformedX[i] = polyX[i];
                transformedY[i] = polyY[i];
            }
            shear(transformedX, transformedY, vertexCount, shx, shy);
            setcolor(CYAN);
            drawPolygon(transformedX, transformedY, vertexCount, CYAN);
            break;
        }
        case 5: {
            // Reflection
            printf("Enter reflection type (1: X-axis, 2: Y-axis, 3: Y = X): ");
            int reflectChoice;
            scanf("%d", &reflectChoice);
            for (int i = 0; i < vertexCount; i++) {
                transformedX[i] = polyX[i];
                transformedY[i] = polyY[i];
            }
            reflect(transformedX, transformedY, vertexCount, reflectChoice);
            setcolor(MAGENTA);
            drawPolygon(transformedX, transformedY, vertexCount, MAGENTA);
            break;
        }
        default:
            printf("Invalid choice.\n");
            break;
    }

    getch();
    closegraph();
    return 0;
}
