#include "graham.h"

bool intersect(Point *a, Point *b, Point *c, Point *d) {
    return ccw_or_collinear(a, b, c) != ccw_or_collinear(a, b, d) &&
           ccw_or_collinear(c, d, a) != ccw_or_collinear(c, d, b);
}

bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections) {
    for (int i = 0; i < start.size(); i++) {
        for (int j = i + 1; j < start.size(); j++) {
            if (intersect(start[i], end[i], start[j], end[j])) {
                intersections.push_back(make_pair(i, j));
            }
        }
    }
}
