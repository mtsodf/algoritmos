#pragma once
#include <string>
#include <vector>

#include "point.h"

using namespace std;

vector<int> *graham(vector<Point *> *points, string sort_alg = "std");
bool ccw_or_collinear(Point *a, Point *b, Point *c);
double get_min_point_index(vector<Point *> points);
