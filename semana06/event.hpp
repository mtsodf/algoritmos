#pragma once
#include "segment.hpp"

const int SEGMENT_START = 0, SEGMENT_END = 1, INTERSECTION = 2;

class Event {
   public:
    Segment *seg;
    Segment *other_seg;
    int type;
    double x;
    double y;
    Event(Segment *seg, Segment *other_seg, int type, double x = 0, double y = 0);
    // override comparison operator <
    bool operator<(const Event &other) const;
};