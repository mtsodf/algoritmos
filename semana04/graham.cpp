#include <fstream>
#include <iostream>
#include <vector>

#include "jarvis.h"

using namespace std;

class Point {
   public:
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

bool ccw(Point *a, Point *b, Point *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x) > 1e-12;
}

double get_min_point_index(vector<Point *> points) {
    double min_value = INFINITY;
    int min_index = 0;
    for (int i = 0; i < points.size(); i++) {
        if (points[i]->y < min_value || (points[i]->y == min_value && points[i]->x < points[min_index]->x)) {
            min_value = points[i]->y;
            min_index = i;
        }
    }
    return min_index;
}

void write_points_on_json(fstream &output, vector<Point *> points) {
    int n = points.size();
    output << "\"points_x\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->x;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"points_y\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->y;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n]";
}

vector<int> *graham(vector<Point *> points) {
    int init_point = get_min_point_index(points);

    Point *base_point = points[init_point];

    // Put init_point at the beginning of the vector
    Point *temp = points[0];
    points[0] = points[init_point];
    points[init_point] = temp;

    cout << "Base point = " << base_point->x << ", " << base_point->y << endl;

    // Sort beggining from second element

    sort(begin(points) + 1, end(points), [&base_point](Point *a, Point *b) {
        return ccw(base_point, a, b);
        // double ang0 = angle(base_point->x, base_point->y, a->x, a->y);
        // double ang1 = angle(base_point->x, base_point->y, b->x, b->y);
        // return ang0 < ang1;
    });

    vector<int> convex_hull;
    convex_hull.reserve(points.size());
    convex_hull.push_back(0);
    convex_hull.push_back(1);

    int n_hull = 2;

    for (int i = 2; i < points.size(); i++) {
        while (!ccw(points[convex_hull[convex_hull.size() - 2]], points[convex_hull[convex_hull.size() - 1]], points[i])) {
            convex_hull.pop_back();
        }
        convex_hull.push_back(i);
    }

    fstream output;
    output.open("output.json", ios::out);
    output << "{\n";
    write_points_on_json(output, points);
    output << "," << endl;
    output << "\"convex_hull\": [\n";
    for (int i = 0; i < convex_hull.size(); i++) {
        output << convex_hull[i];
        if (i < convex_hull.size() - 1) {
            output << ",\n";
        }
    }
    output << "]" << endl;

    output << "}\n";
    output.close();

    return NULL;
}
