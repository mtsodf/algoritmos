#pragma once

#include "point.h"

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
    // Override comparison operator ==
    bool operator==(const Segment &other) const {
        return this->id == other.id;
    }
    bool operator>(const Segment &other) const {
        return (!(*this == other)) && (!(*this < other));
    }
};