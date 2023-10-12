#pragma once

#include <string>
#include <vector>

#include "point.h"

using namespace std;

class Segment {
   public:
    Point *start;
    Point *end;
    int id;
    double *current_x;
    Segment(Point *p0, Point *p1, int id);
    double y_value(double x) const;
    void calc_intersection(const Segment &other, double &x, double &y);
    // Override comparison operator <
    bool operator<(const Segment &other) const {
        return this->y_value(*current_x) < other.y_value(*current_x);
    }
};
bool intersect(Point *a, Point *b, Point *c, Point *d);
bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections, bool detection = true);
bool naive_segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersections, bool detection = true);
bool segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersection_pairs, const string &container_type, bool detection = true);
bool segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersection_pairs, const string &container_type, const string &events_filename = "", bool detection = true);
void generate_segments(int n, double length_mean, double length_std, vector<Segment *> &segments);
void generate_segments_no_intersect(int n, vector<Segment *> &segments);
void generate_big_segments_no_intersect(int n, vector<Segment *> &segments);
void read_segments_from_file(string input_file, vector<Segment *> &segments);