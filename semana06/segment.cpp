#include "segment.hpp"

#include "point.h"
void Segment::calc_intersection(const Segment &other, double &x, double &y) {
    double a0 = (this->end->y - this->start->y) / (this->end->x - this->start->x);
    double b0 = -a0 * this->start->x + this->start->y;
    double a1 = (other.end->y - other.start->y) / (other.end->x - other.start->x);
    double b1 = -a1 * other.start->x + other.start->y;
    x = (b1 - b0) / (a0 - a1);
    y = a0 * x + b0;
}

Segment::Segment(Point *p0, Point *p1, int id) {
    if (p0->x < p1->x || (p0->x == p1->x && p0->y < p1->y)) {
        this->start = p0;
        this->end = p1;
    } else {
        this->start = p1;
        this->end = p0;
    }
    this->id = id;
}

double Segment::y_value(double x) const {
    double m = (end->y - start->y) / (end->x - start->x);
    double b = start->y - m * start->x;
    return m * x + b;
}