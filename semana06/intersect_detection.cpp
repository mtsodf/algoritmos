#include <fstream>
#include <iostream>
#include <random>

#include "data_structures.hpp"
#include "graham.h"
#include "intersection_detection.h"

using namespace std;

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

void generate_segments(int n, double length_mean, double length_std, vector<Segment *> &segments) {
    // Create a random number generator engine
    random_device rd;                                                  // Seed the random number generator
    mt19937 gen(rd());                                                 // Mersenne Twister PRNG
    normal_distribution<double> length_dist(length_mean, length_std);  // Specify mean and standard deviation
    uniform_real_distribution<double> theta_dist(-M_PI, M_PI);
    uniform_real_distribution<double> point_dist(0, 1);

    int id = segments.size();
    for (int i = 0; i < n; i++) {
        // Generate a random normal value
        double random_length = length_dist(gen);

        if (random_length < 0) random_length = 0.0;
        double theta = theta_dist(gen);

        double x0 = point_dist(gen), y0 = point_dist(gen);
        double x1, y1;

        x1 = x0 + random_length * cos(theta);
        y1 = y0 + random_length * sin(theta);

        segments.push_back(new Segment(new Point(x0, y0), new Point(x1, y1), id++));
    }
}

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

bool segment_intersection(vector<Segment *> &segments, pair<int, int> &intersection_pair, const string &container_type, const string &events_filename) {
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
        events.push_back(new Event(segments[i], SEGMENT_START));
        events.push_back(new Event(segments[i], SEGMENT_END));
    }

    sort(events.begin(), events.end(), [](Event *a, Event *b) {
        if (a->x == b->x) {
            return a->type < b->type;
        }
        return a->x < b->x;
    });
    SegmentContainer *segment_container;
    if (container_type == "list")
        segment_container = new SegmentVector();
    else if (container_type == "unordered_list") {
        segment_container = new UnorderedList();
    } else {
        cout << "Invalid container type " << container_type << endl;
        exit(1);
    }

    for (int i = 0; i < events.size(); i++) {
        Segment *cur_seg = events[i]->seg;
        if (events[i]->type == SEGMENT_START) {
            if (verbose) {
                events_file << "Start;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }
            segment_container->add(cur_seg);

            if (verbose) {
                log_ids(segment_container, events_file);
            }
            Segment *prev = segment_container->prev(cur_seg);
            if (prev != nullptr) {
                if (verbose) events_file << cur_seg->id << " == " << prev->id << ";";
                if (intersect(cur_seg, prev)) {
                    if (verbose) events_file << "true; ";
                    intersection_pair = {cur_seg->id, prev->id};
                    return true;
                } else {
                    if (verbose) events_file << "false; ";
                }
            }
            Segment *next = segment_container->next(cur_seg);
            if (next != nullptr) {
                if (verbose) events_file << cur_seg->id << " == " << next->id << ";";
                if (intersect(cur_seg, next)) {
                    if (verbose) events_file << "true; ";
                    intersection_pair = {cur_seg->id, next->id};
                    return true;
                } else {
                    if (verbose) events_file << "false; ";
                }
            }
            if (verbose) events_file << endl;
        } else if (events[i]->type == SEGMENT_END) {
            if (verbose) {
                events_file << "End;  " << cur_seg->id << "; ";
                log_ids(segment_container, events_file);
            }

            Segment *prev = segment_container->prev(cur_seg);
            Segment *next = segment_container->next(cur_seg);

            if (prev != nullptr && next != nullptr) {
                if (verbose) events_file << prev->id << " == " << next->id << ";";
                if (intersect(prev, next)) {
                    if (verbose) events_file << "true; ";
                    intersection_pair = {prev->id, next->id};
                    return true;
                } else {
                    if (verbose) events_file << "false; ";
                }
            }
            segment_container->remove(cur_seg);
            if (verbose) {
                log_ids(segment_container, events_file);
                events_file << endl;
            }
        }
    }

    if (verbose) events_file.close();

    return false;
}

bool segment_intersection(vector<Point *> &start, vector<Point *> &end, pair<int, int> &intersection_pair, const string &container_type) {
    int n = start.size();
    vector<Segment *> segments;
    segments.reserve(n);
    for (int i = 0; i < start.size(); i++) {
        segments.push_back(new Segment(start[i], end[i], i));
    }
    return segment_intersection(segments, intersection_pair, container_type);
}