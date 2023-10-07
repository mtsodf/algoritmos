
#include <iostream>
#include <vector>

#include "intersection_detection.h"
#include "point.h"

int main() {
    vector<Point *> start, end;
    start.push_back(new Point(1, 1));
    end.push_back(new Point(3, 2));

    start.push_back(new Point(3.5, 3.5));
    end.push_back(new Point(5.5, 2));

    start.push_back(new Point(4, 0.5));
    end.push_back(new Point(5, 3.5));

    pair<int, int> intersection_pair;
    bool found = segment_intersection(start, end, intersection_pair);
    cout << "Found = " << found << endl;
    cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;

    start.push_back(new Point(3.4, 1));
    end.push_back(new Point(0.5, 2));

    found = segment_intersection(start, end, intersection_pair);
    cout << "Found = " << found << endl;
    cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;
}