#pragma once

#include <fstream>

#include "point.h"
using namespace std;

void write_points_on_json(fstream &output, vector<Point *> points);
void write_int_matrix_on_json(fstream &output, vector<vector<int>> matrix, string name);