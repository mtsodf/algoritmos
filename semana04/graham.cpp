#include "graham.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "jarvis.h"
#include "point.h"
#include "sort_algs.h"

using namespace std;

bool ccw(Point *a, Point *b, Point *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x) >= 1e-12;
}

double EPSILON = 1e-6;

bool ccw_or_collinear(Point *a, Point *b, Point *c) {
    double cross = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
    if (cross > EPSILON) {
        return true;
    } else if (cross < -EPSILON) {
        return false;
    } else {
        return a->dist(b) < a->dist(c);
    }
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

vector<int> *graham(vector<Point *> *points, string sort_alg) {
    int init_point = get_min_point_index(*points);

    Point *base_point = (*points)[init_point];

    // Put init_point at the beginning of the vector
    Point *temp = (*points)[0];
    (*points)[0] = (*points)[init_point];
    (*points)[init_point] = temp;

    cout << "Base point = " << base_point->x << ", " << base_point->y << endl;

    function<bool(Point *, Point *)> comparator = [&base_point](Point *a, Point *b) {
        return ccw_or_collinear(base_point, a, b);
    };

    // Sort beggining from second element
    if (sort_alg == "std") {
        sort(begin(*points) + 1, end(*points), comparator);
    } else if (sort_alg == "selection") {
        selection_sort(points, 1, points->size(), comparator);
    } else if (sort_alg == "heap") {
        heap_sort(points, 1, points->size(), comparator);
    } else if (sort_alg == "quick") {
        quick_sort(points, 1, points->size(), comparator);
    } else if (sort_alg == "insertion") {
        insertion_sort(points, 1, points->size(), comparator);
    } else if (sort_alg == "merge") {
        merge_sort(points, 1, points->size(), comparator);
    } else {
        cout << "Algorithm " << sort_alg << " not available." << endl;
    }

    vector<int> *convex_hull = new vector<int>;
    convex_hull->reserve(points->size());
    convex_hull->push_back(0);
    convex_hull->push_back(1);

    int n_hull = 2;
    Point *a, *b;
    for (int i = 2; i < points->size(); i++) {
        a = (*points)[(*convex_hull)[convex_hull->size() - 2]];
        b = (*points)[(*convex_hull)[convex_hull->size() - 1]];
        while (!ccw_or_collinear(a, b, (*points)[i])) {
            convex_hull->pop_back();
            a = (*points)[(*convex_hull)[convex_hull->size() - 2]];
            b = (*points)[(*convex_hull)[convex_hull->size() - 1]];
        }
        convex_hull->push_back(i);
    }
    cout << "Convex hull size = " << convex_hull->size() << endl;
    return convex_hull;
}
