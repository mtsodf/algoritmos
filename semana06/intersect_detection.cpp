#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

#include "data_structures.hpp"
#include "event.hpp"
#include "graham.h"
#include "intersection_detection.h"
#include "segment.hpp"

using namespace std;

bool intersect(Point *a, Point *b, Point *c, Point *d) {
    return ccw_or_collinear(a, b, c) != ccw_or_collinear(a, b, d) &&
           ccw_or_collinear(c, d, a) != ccw_or_collinear(c, d, b);
}

bool intersect(Segment *a, Segment *b) {
    return intersect(a->start, a->end, b->start, b->end);
}

void add_intersection_event(vector<Event *> &events, Segment *s0, Segment *s1) {
    double x_intersect, y_intersect;
    s0->calc_intersection(*s1, x_intersect, y_intersect);
    events.push_back(new Event(s0, s1, INTERSECTION, x_intersect, y_intersect));
    int j = events.size() - 1;
    for (j = events.size() - 1; j >= 1; j--) {
        if (events[j]->x < events[j - 1]->x) {
            std::swap(*events[j], *events[j - 1]);
        } else {
            break;
        }
    }
}

void intersection_found(vector<Event *> &events, Segment *s0, Segment *s1, double current_x) {
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

bool equal_intersection_events(Event *a, Event *b) {
    if (a == nullptr || b == nullptr) return false;

    return a->type == INTERSECTION && b->type == INTERSECTION && a->seg->id == b->seg->id && a->other_seg->id == b->other_seg->id;
}

bool test_intersection(Segment *a, Segment *b, vector<Event *> &events, vector<pair<int, int>> &intersections_pairs, double current_x, fstream &events_file) {
    if (a == nullptr || b == nullptr) return false;
    if (events_file.is_open()) events_file << a->id << " == " << b->id << ";";
    if (intersect(a, b)) {
        if (events_file.is_open()) events_file << "true; ";
        intersection_found(events, a, b, current_x);
    } else {
        if (events_file.is_open()) events_file << "false; ";
    }
    return false;
}

bool segment_intersection(vector<Segment *> &segments, vector<pair<int, int>> &intersection_pairs, const string &container_type, const string &events_filename, bool detection) {
    bool verbose = false;

    fstream events_file;
    if (!events_filename.empty()) {
        events_file.open(events_filename, ios::out);
        verbose = true;
    }
    int n = segments.size();
    vector<Event *> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        events.push_back(new Event(segments[i], nullptr, SEGMENT_START));
        events.push_back(new Event(segments[i], nullptr, SEGMENT_END));
    }

    double current_x;
    for (int i = 0; i < n; i++) {
        segments[i]->current_x = &current_x;
    }

    sort(events.begin(), events.end(), [](Event *a, Event *b) {
        if (a->x == b->x) {
            return a->type < b->type;
        }
        return a->x < b->x;
    });
    SegmentContainer *segment_container = segment_container_factory(container_type, n);

    Event *last_event = nullptr;
    for (int i = 0; i < events.size(); i++) {
        if (equal_intersection_events(events[i], last_event)) continue;

        last_event = events[i];
        Segment *cur_seg = events[i]->seg;
        if (events[i]->type == SEGMENT_START) {
            current_x = events[i]->x;
            if (verbose) {
                events_file << "Start;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }
            segment_container->add(cur_seg);

            if (verbose) log_ids(segment_container, events_file);

            Segment *prev = segment_container->prev(cur_seg);
            if (test_intersection(prev, cur_seg, events, intersection_pairs, current_x, events_file) && detection) {
                return true;
            };
            Segment *next = segment_container->next(cur_seg);
            if (test_intersection(cur_seg, next, events, intersection_pairs, current_x, events_file) && detection) {
                return true;
            };
            if (verbose) events_file << endl;
        } else if (events[i]->type == SEGMENT_END) {
            current_x = events[i]->x;
            if (verbose) {
                events_file << "End;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }

            Segment *prev = segment_container->prev(cur_seg);
            Segment *next = segment_container->next(cur_seg);
            if (test_intersection(prev, next, events, intersection_pairs, current_x, events_file) && detection) {
                return true;
            };

            segment_container->remove(cur_seg);
            if (verbose) {
                log_ids(segment_container, events_file);
                events_file << endl;
            }
        } else if (events[i]->type == INTERSECTION) {
            current_x = (events[i]->x + current_x) / 2;
            add_intersection(intersection_pairs, events[i]->seg, events[i]->other_seg);
            Segment *upper = segment_container->next(events[i]->other_seg);
            Segment *lower = segment_container->prev(events[i]->seg);
            segment_container->swap(events[i]->seg, events[i]->other_seg);
            current_x = events[i]->x;

            test_intersection(events[i]->seg, upper, events, intersection_pairs, current_x, events_file);
            test_intersection(lower, events[i]->other_seg, events, intersection_pairs, current_x, events_file);

            if (verbose) {
                events_file << events[i]->seg->id << " intersect " << events[i]->other_seg->id << ";";
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
    return segment_intersection(segments, intersection_pairs, container_type, "", detection = detection);
}
