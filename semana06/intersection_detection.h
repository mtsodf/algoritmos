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
    Segment(Point *p0, Point *p1, int id);
    double y_value(double x) const;
    // Override comparison operator <
    bool operator<(const Segment &other) const {
        double cur_y = this->start->y;
        double other_y = other.y_value(this->start->x);
        return cur_y < other_y;
    }
};
bool intersect(Point *a, Point *b, Point *c, Point *d);
bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections);
bool naive_segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersections);
bool segment_intersection(vector<Point *> &start, vector<Point *> &end, pair<int, int> &intersection_pair, const string &container_type);
bool segment_intersection(vector<Segment *> &segments, pair<int, int> &intersection_pair, const string &container_type, const string &events_filename = "");
void generate_segments(int n, double length_mean, double length_std, vector<Segment *> &segments);
void generate_segments_no_intersect(int n, vector<Segment *> &segments);
void generate_big_segments_no_intersect(int n, vector<Segment *> &segments);
void read_segments_from_file(string input_file, vector<Segment *> &segments);