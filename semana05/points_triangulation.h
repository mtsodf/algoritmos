#pragma once
#include "point.h"
#include "polygon.h"

void triangulate_convex_polygon(vector<int> &points_int, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list);
void write_triangulation_json(vector<Point *> *points, vector<vector<int>> *triangles, vector<vector<int>> *adjacency_list, string alg, double time_seconds, vector<int> &path, string filename);
void triangulate_trig(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list);

void triangulate_graham(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list);
void find_path_from_baricenter_to_outside(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list, vector<int> &path);