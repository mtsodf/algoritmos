#pragma once
#include "intersection_detection.h"
// Create abstract class of container of segments
class SegmentContainer {
   public:
    virtual void add(Segment *s) = 0;
    virtual void remove(Segment *s) = 0;
    virtual Segment *next(Segment *s) = 0;
    virtual Segment *prev(Segment *s) = 0;
    virtual Segment *get_segment(int id) = 0;
    virtual void swap(Segment *s1, Segment *s2) = 0;
    virtual int size() = 0;
};