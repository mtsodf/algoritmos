#pragma once

#include <string>
#include <vector>

#include "event.hpp"
#include "point.h"
#include "segment.hpp"

using namespace std;

bool intersect(Point *a, Point *b, Point *c, Point *d);

bool intersect(Segment *a, Segment *b);
bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections, bool detection = true);
bool naive_segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersections, bool detection = true);
bool segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersection_pairs, const string &container_type, bool detection = true);
bool segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersection_pairs, const string &container_type, const string &events_filename = "", bool detection = true);
void generate_segments(int n, double length_mean, double length_std, vector<Segment *> &segments);
void generate_grid(int n, vector<Segment *> &segments);
void generate_vert_grid(int nx, int ny, vector<Segment *> &segments);
void generate_segments_no_intersect(int n, vector<Segment *> &segments);
void generate_big_segments_no_intersect(int n, vector<Segment *> &segments);
void read_segments_from_file(string input_file, vector<Segment *> &segments);