#include <iostream>

#include "graham.h"

using namespace std;

class Segment {
   public:
    Point *start;
    Point *end;
    int id;
    Segment(Point *p0, Point *p1, int id) {
        if (p0->x < p1->x || (p0->x == p1->x && p0->y < p1->y)) {
            this->start = p0;
            this->end = p1;
        } else {
            this->start = p1;
            this->end = p0;
        }
        this->start = start;
        this->end = end;
        this->id = id;
    }

    double y_value(double x) {
        double m = (end->y - start->y) / (end->x - start->x);
        double b = start->y - m * start->x;
        return m * x + b;
    }
};

bool intersect(Point *a, Point *b, Point *c, Point *d) {
    return ccw_or_collinear(a, b, c) != ccw_or_collinear(a, b, d) &&
           ccw_or_collinear(c, d, a) != ccw_or_collinear(c, d, b);
}

bool intersect(Segment *a, Segment *b) {
    return intersect(a->start, a->end, b->start, b->end);
}

int SEGMENT_START = 0, SEGMENT_END = 1, INTERSECTION = 2;

class Event {
   public:
    Segment *seg;
    int type;
    double x;
    Event(Segment *seg, int type, double x = 0) {
        this->seg = seg;
        this->type = type;
        if (type == SEGMENT_START) {
            this->x = seg->start->x;
        } else if (type == SEGMENT_END) {
            this->x = seg->end->x;
        } else {
            this->x = x;
        }
    }
};

bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections) {
    for (int i = 0; i < start.size(); i++) {
        for (int j = i + 1; j < start.size(); j++) {
            if (intersect(start[i], end[i], start[j], end[j])) {
                intersections.push_back(make_pair(i, j));
            }
        }
    }
}

bool segment_intersection(vector<Point *> &start, vector<Point *> &end, pair<int, int> &intersection_pair) {
    int n = start.size();
    vector<Segment *> segments;
    segments.reserve(n);
    for (int i = 0; i < start.size(); i++) {
        segments.push_back(new Segment(start[i], end[i], i));
    }

    vector<Event *> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        events.push_back(new Event(segments[i], SEGMENT_START));
        events.push_back(new Event(segments[i], SEGMENT_END));
    }

    sort(events.begin(), events.end(), [](Event *a, Event *b) {
        if (a->x == b->x) {
            return a->type < b->type;
        }
        return a->x < b->x;
    });

    vector<Segment *> active_segments;

    for (int i = 0; i < events.size(); i++) {
        if (events[i]->type == SEGMENT_START) {
            Segment *cur_seg = events[i]->seg;
            active_segments.push_back(cur_seg);

            double cur_x = cur_seg->start->x;
            double cur_y = cur_seg->start->y;
            int seg_pos;
            for (seg_pos = active_segments.size() - 1; seg_pos >= 1; seg_pos--) {
                if (cur_y > active_segments[seg_pos - 1]->y_value(cur_x)) {
                    swap(active_segments[seg_pos], active_segments[seg_pos - 1]);
                } else {
                    break;
                }
            }

            if (seg_pos > 0) {
                if (intersect(cur_seg, active_segments[seg_pos - 1])) {
                    intersection_pair = {cur_seg->id, active_segments[seg_pos - 1]->id};
                    return true;
                }
            }
            if (seg_pos < active_segments.size() - 1) {
                if (intersect(cur_seg, active_segments[seg_pos + 1])) {
                    intersection_pair = {cur_seg->id, active_segments[seg_pos + 1]->id};
                    return true;
                }
            }
        } else if (events[i]->type == SEGMENT_END) {
            int seg_pos;
            for (seg_pos = 0; seg_pos < active_segments.size(); seg_pos++) {
                if (events[i]->seg->id == active_segments[seg_pos]->id) break;
            }

            if (seg_pos > 0 && seg_pos < active_segments.size() - 1) {
                if (intersect(active_segments[seg_pos - 1], active_segments[seg_pos + 1])) {
                    intersection_pair = {active_segments[seg_pos - 1]->id,
                                         active_segments[seg_pos + 1]->id};
                    return true;
                }
            }
            for (int j = seg_pos; j < active_segments.size() - 1; j++) {
                swap(active_segments[j], active_segments[j + 1]);
            }
            active_segments.pop_back();
        }
    }

    return false;
}
