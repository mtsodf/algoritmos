#pragma once

#include <vector>

#include "point.h"

using namespace std;

bool intersect(Point *a, Point *b, Point *c, Point *d);
bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections);