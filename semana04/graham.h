#pragma once
#include <vector>

using namespace std;
// Add Point definition
class Point {
   public:
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};
vector<int> *graham(vector<Point *> points);