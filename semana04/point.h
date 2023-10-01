#pragma once

#include <math.h>

// Add Point definition
class Point {
   public:
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double dist(Point *p) {
        return sqrt(pow(this->x - p->x, 2) + pow(this->y - p->y, 2));
    }
};