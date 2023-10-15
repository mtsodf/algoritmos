#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

#include "data_structures.hpp"
#include "event.hpp"
#include "intersection_detection.h"
#include "segment.hpp"

using namespace std;

double EPSILON = 0;

bool ccw_or_collinear(Point *a, Point *b, Point *c) {
    double cross = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
    if (cross > EPSILON) {
        return true;
    } else if (cross < -EPSILON) {
        return false;
    } else {
        return a->dist(b) < a->dist(c);
    }
}

bool intersect(Point *a, Point *b, Point *c, Point *d) {
    return ccw_or_collinear(a, b, c) != ccw_or_collinear(a, b, d) &&
           ccw_or_collinear(c, d, a) != ccw_or_collinear(c, d, b);
}

bool intersect(Segment *a, Segment *b) {
    return intersect(a->start, a->end, b->start, b->end);

    double x, y;
    a->calc_intersection(*b, x, y);
    double xa_max = max(a->start->x, a->end->x);
    double xb_max = max(b->start->x, b->end->x);
    if (x > xa_max || x > xb_max) return false;

    double xa_min = min(a->start->x, a->end->x);
    double xb_min = min(b->start->x, b->end->x);
    if (x < xa_min || x < xb_min) return false;

    double ya_max = max(a->start->y, a->end->y);
    double yb_max = max(b->start->y, b->end->y);
    if (y > ya_max || y > yb_max) return false;

    double ya_min = min(a->start->y, a->end->y);
    double yb_min = min(b->start->y, b->end->y);
    if (y < ya_min || y < yb_min) return false;

    return true;
}

void add_intersection_event(EventContainer &events, Segment *s0, Segment *s1) {
    double x_intersect, y_intersect;
    s0->calc_intersection(*s1, x_intersect, y_intersect);
    events.add(new Event(s0, s1, INTERSECTION, x_intersect, y_intersect));
}

void intersection_found(EventContainer &events, Segment *s0, Segment *s1, double current_x) {
    double x_intersect, y_intersect;
    s0->calc_intersection(*s1, x_intersect, y_intersect);
    if (x_intersect > current_x) {
        add_intersection_event(events, s0, s1);
    }
}

void add_intersection(vector<pair<int, int>> &intersections, Segment *s0, Segment *s1) {
    if (s0->id < s1->id)
        intersections.push_back({s0->id, s1->id});
    else
        intersections.push_back({s1->id, s0->id});
}

bool naive_segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersections, bool detection) {
    for (int i = 0; i < segments.size(); i++) {
        for (int j = i + 1; j < segments.size(); j++) {
            if (intersect(segments[i], segments[j])) {
                intersections.push_back(make_pair(i, j));
                if (detection) return true;
            }
        }
    }
    return intersections.size() > 0;
}

bool naive_segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersections, bool detection) {
    for (int i = 0; i < start.size(); i++) {
        for (int j = i + 1; j < start.size(); j++) {
            if (intersect(start[i], end[i], start[j], end[j])) {
                intersections.push_back(make_pair(i, j));
                if (detection) return true;
            }
        }
    }

    return intersections.size() > 0;
}

void log_ids(SegmentContainer *segments, fstream &events_file) {
    events_file << "[";
    Segment *current = segments->first();
    while (current != nullptr) {
        events_file << current->id << ", ";
        current = segments->next(current);
    }
    events_file << "];";
}

SegmentContainer *segment_container_factory(string container_type, int n) {
    SegmentContainer *segment_container;
    if (container_type == "list")
        segment_container = new SegmentVector(n);
    else if (container_type == "unordered_list") {
        segment_container = new UnorderedList(n);
    } else if (container_type == "binary_tree") {
        segment_container = new BinaryTree();
    } else {
        cout << "Invalid container type " << container_type << endl;
        exit(1);
    }

    return segment_container;
}
EventContainer *event_container_factory(string container_type, int n) {
    EventContainer *event_container;
    if (container_type == "list") {
        event_container = new EventContainerList(n);
    } else if (container_type == "heap") {
        event_container = new EventContainerHeap(n);
    } else {
        cout << "Invalid container type " << container_type << endl;
        exit(1);
    }
    return event_container;
}

bool equal_intersection_events(Event *a, Event *b) {
    if (a == nullptr || b == nullptr) return false;

    return a->type == INTERSECTION && b->type == INTERSECTION && a->seg->id == b->seg->id && a->other_seg->id == b->other_seg->id;
}

bool test_intersection(Segment *a, Segment *b, EventContainer &events, vector<pair<int, int>> &intersections_pairs, double current_x, fstream &events_file) {
    if (a == nullptr || b == nullptr) return false;
    if (events_file.is_open()) events_file << a->id << " == " << b->id << ";";
    if (intersect(a, b)) {
        if (events_file.is_open()) events_file << "true; ";
        intersection_found(events, a, b, current_x);
        return true;
    } else {
        if (events_file.is_open()) events_file << "false; ";
    }
    return false;
}

bool segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersection_pairs, const string &segments_container_type, const string &event_container_type, const string &events_filename, bool detection) {
    bool verbose = false;

    fstream events_file;
    if (!events_filename.empty()) {
        events_file.open(events_filename, ios::out);
        verbose = true;
    }
    int n = segments.size();
    EventContainer *events = event_container_factory(event_container_type, n);

    for (int i = 0; i < n; i++) {
        events->add_no_initialize(new Event(segments[i], nullptr, SEGMENT_START));
        events->add_no_initialize(new Event(segments[i], nullptr, SEGMENT_END));
    }
    events->initialize();

    double current_x;
    for (int i = 0; i < n; i++) {
        segments[i]->current_x = &current_x;
    }

    SegmentContainer *segment_container = segment_container_factory(segments_container_type, n);

    Event *last_event = nullptr;
    Event *cur_event;
    while (events->size() > 0) {
        cur_event = events->pop();
        if (equal_intersection_events(cur_event, last_event)) continue;

        last_event = cur_event;
        Segment *cur_seg = cur_event->seg;
        if (cur_event->type == SEGMENT_START) {
            current_x = cur_event->x;
            if (verbose) {
                events_file << "Start;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }
            segment_container->add(cur_seg);

            if (verbose) log_ids(segment_container, events_file);

            Segment *prev = segment_container->prev(cur_seg);
            if (test_intersection(prev, cur_seg, *events, intersection_pairs, current_x, events_file) && detection) {
                add_intersection(intersection_pairs, prev, cur_seg);
                return true;
            };
            Segment *next = segment_container->next(cur_seg);
            if (test_intersection(cur_seg, next, *events, intersection_pairs, current_x, events_file) && detection) {
                add_intersection(intersection_pairs, cur_seg, next);
                return true;
            };
            if (verbose) events_file << endl;
        } else if (cur_event->type == SEGMENT_END) {
            current_x = cur_event->x;
            if (verbose) {
                events_file << "End;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }

            Segment *prev = segment_container->prev(cur_seg);
            Segment *next = segment_container->next(cur_seg);
            if (test_intersection(prev, next, *events, intersection_pairs, current_x, events_file) && detection) {
                add_intersection(intersection_pairs, prev, next);
                return true;
            };

            segment_container->remove(cur_seg);
            if (verbose) {
                log_ids(segment_container, events_file);
                events_file << endl;
            }
        } else if (cur_event->type == INTERSECTION) {
            current_x = (cur_event->x + current_x) / 2;
            add_intersection(intersection_pairs, cur_event->seg, cur_event->other_seg);
            Segment *upper = segment_container->next(cur_event->other_seg);
            Segment *lower = segment_container->prev(cur_event->seg);
            segment_container->swap(cur_event->seg, cur_event->other_seg);
            current_x = cur_event->x;

            test_intersection(cur_event->seg, upper, *events, intersection_pairs, current_x, events_file);
            test_intersection(lower, cur_event->other_seg, *events, intersection_pairs, current_x, events_file);

            if (verbose) {
                events_file << cur_event->seg->id << " intersect " << cur_event->other_seg->id << ";";
                log_ids(segment_container, events_file);
                events_file << endl;
            }
        }
    }

    if (verbose) events_file.close();

    return intersection_pairs.size();
}

bool segment_intersection(vector<Point *> &start, vector<Point *> &end, vector<pair<int, int>> &intersection_pairs, const string &container_type, bool detection) {
    int n = start.size();
    vector<Segment *> segments;
    segments.reserve(n);
    for (int i = 0; i < start.size(); i++) {
        segments.push_back(new Segment(start[i], end[i], i));
    }
    return segment_intersection(segments, intersection_pairs, container_type, "heap", "", detection = detection);
}
