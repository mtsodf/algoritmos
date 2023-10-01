#pragma once
#include "point.h"
#include "polygon.h"

void triangulate_convex_polygon(vector<int> &points_int, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list);
void write_triangulation_json(vector<Point *> *points, vector<vector<int>> *triangles, vector<vector<int>> *adjacency_list, double time_seconds, string filename);
void triangulate_trig(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list);