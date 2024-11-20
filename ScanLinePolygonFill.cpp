#include <graphics.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int xMin, yMin, xMax, yMax;
    float inverseSlope;
};

void scanLineFill(vector<int> &xPoints, vector<int> &yPoints, int n, int fillColor) {
    vector<Edge> edges;
    int yMin = INT_MAX, yMax = INT_MIN;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (yPoints[i] > yPoints[j]) {
            swap(xPoints[i], xPoints[j]);
            swap(yPoints[i], yPoints[j]);
        }

        if (yPoints[i] != yPoints[j]) {
            edges.push_back({xPoints[i], yPoints[i], xPoints[j], yPoints[j], (float)(xPoints[j] - xPoints[i]) / (yPoints[j] - yPoints[i])});
        }
        if (yPoints[i] < yMin)
            yMin = yPoints[i];
        if (yPoints[i] > yMax)
            yMax = yPoints[i];
    }

    for (int y = yMin; y <= yMax; y++) {
        vector<int> intersections;
        for (auto &edge : edges) {
            if (y >= edge.yMin && y < edge.yMax) {
                int x = edge.xMin + (y - edge.yMin) * edge.inverseSlope;
                intersections.push_back(x);
            }
        }

        sort(intersections.begin(), intersections.end());

        for (int i = 0; i < intersections.size(); i += 2) {
            for (int x = intersections[i]; x < intersections[i + 1]; x++) {
                putpixel(x, y, fillColor);
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int fillColor;
    vector<int> xPoints, yPoints;
    int x, y;

    cout << "Enter fill color: 1 for RED, 2 for GREEN, 3 for BLUE, 4 for WHITE: ";
    cin >> fillColor;

    cout << "Click to define the vertices of the polygon. Right-click to stop." << endl;

    while (true) {
        while (!ismouseclick(WM_LBUTTONDOWN) && !ismouseclick(WM_RBUTTONDOWN)) {}

        if (ismouseclick(WM_RBUTTONDOWN)) {
            break;
        }

        getmouseclick(WM_LBUTTONDOWN, x, y);
        xPoints.push_back(x);
        yPoints.push_back(y);
        putpixel(x, y, WHITE);

        if (xPoints.size() > 1) {
            line(xPoints[xPoints.size() - 2], yPoints[yPoints.size() - 2], x, y);
        }
    }

    if (xPoints.size() > 1) {
        line(xPoints[xPoints.size() - 1], yPoints[yPoints.size() - 1], xPoints[0], yPoints[0]);
    }

    cout << "Polygon complete. Now, the polygon will be filled." << endl;

    scanLineFill(xPoints, yPoints, xPoints.size(), fillColor);

    getch();
    closegraph();
    return 0;
}
