#pragma once
#include <string>
#include <vector>

#include "point.h"

using namespace std;

vector<int> *graham(vector<Point *> *points, string sort_alg = "std");
