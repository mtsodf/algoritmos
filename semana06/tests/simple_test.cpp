
#include <iostream>
#include <vector>

#include "data_structures.hpp"
#include "intersection_detection.h"
#include "point.h"

int main() {
    vector<Segment *> segments;
    int id = 0;
    segments.push_back(new Segment(new Point(1, 1), new Point(7, 4), id++));
    segments.push_back(new Segment(new Point(2, 3), new Point(6, 1), id++));
    segments.push_back(new Segment(new Point(4, 1.5), new Point(7, 1.5), id++));

    vector<pair<int, int>> intersections;

    segment_intersection(segments, intersections, "unordered_list", "", false);
    cout << "FINISHED" << endl;
}