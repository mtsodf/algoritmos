#pragma once
#include "intersection_detection.h"
// Create abstract class of container of segments
class SegmentContainer {
   public:
    virtual void add(Segment *s) = 0;
    virtual void remove(Segment *s) = 0;
    virtual Segment *next(Segment *s) = 0;
    virtual Segment *prev(Segment *s) = 0;
    // virtual Segment *get_segment(int id) = 0;
    virtual Segment *first() = 0;
    virtual void swap(Segment *s1, Segment *s2) = 0;
    virtual int size() = 0;
};

class SegmentVector : public SegmentContainer {
   protected:
    vector<Segment *> segments;

   public:
    SegmentVector() {}
    void add(Segment *s);
    void remove(Segment *s);
    Segment *next(Segment *s);
    Segment *prev(Segment *s);
    Segment *get_segment(int id);
    Segment *first();
    void swap(Segment *s1, Segment *s2);
    int size();
    int find_pos(Segment *s);
};

class UnorderedList : public SegmentVector {
   private:
   public:
    UnorderedList() {}
    void add(Segment *s);
    Segment *next(Segment *s);
    Segment *prev(Segment *s);
    Segment *first();
};