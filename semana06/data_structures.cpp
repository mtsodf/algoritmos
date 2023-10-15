#include "data_structures.hpp"

#include "intersection_detection.h"

void SegmentVector::add(Segment *s) {
    double cur_y = s->start->y;
    double cur_x = s->start->x;

    segments.push_back(s);
    int seg_pos;
    for (seg_pos = segments.size() - 1; seg_pos >= 1; seg_pos--) {
        if (cur_y < segments[seg_pos - 1]->y_value(cur_x)) {
            std::swap(segments[seg_pos], segments[seg_pos - 1]);
        } else {
            break;
        }
    }
}

int SegmentVector::find_pos(Segment *s) {
    int seg_pos = -1;
    for (seg_pos = 0; seg_pos < segments.size(); seg_pos++) {
        if (s->id == segments[seg_pos]->id) break;
    }
    return seg_pos;
}

void SegmentVector::remove(Segment *s) {
    int seg_pos = find_pos(s);

    for (int j = seg_pos; j < segments.size() - 1; j++) {
        std::swap(segments[j], segments[j + 1]);
    }

    segments.pop_back();
}
Segment *SegmentVector::next(Segment *s) {
    int pos = find_pos(s);
    if (pos < segments.size() - 1) {
        return segments[pos + 1];
    } else {
        return nullptr;
    }
}
Segment *SegmentVector::prev(Segment *s) {
    int pos = find_pos(s);
    if (pos > 0) {
        return segments[pos - 1];
    } else {
        return nullptr;
    }
}

Segment *SegmentVector::get_segment(int id) {
    for (int i = 0; i < segments.size(); i++) {
        if (segments[i]->id == id) {
            return segments[i];
        }
    }
    return nullptr;
}
void SegmentVector::swap(Segment *s1, Segment *s2) {
    for (int i = 0; i < segments.size(); i++) {
        if (segments[i]->id == s1->id) {
            segments[i] = s2;
        } else if (segments[i]->id == s2->id) {
            segments[i] = s1;
        }
    }
}
int SegmentVector::size() { return segments.size(); }

Segment *SegmentVector::first() {
    if (size() > 0) {
        return segments[0];
    }
    return nullptr;
}
void UnorderedList::add(Segment *s) {
    segments.push_back(s);
}

Segment *UnorderedList::next(Segment *s) {
    int next_pos = -1;
    for (int i = 0; i < size(); i++) {
        if (s->id == segments[i]->id) continue;
        if (*segments[i] < *s) continue;

        if (next_pos < 0 || *segments[i] < *segments[next_pos]) {
            next_pos = i;
        }
    }
    if (next_pos >= 0) {
        return segments[next_pos];
    } else {
        return nullptr;
    }
}

Segment *UnorderedList::prev(Segment *s) {
    int prev_pos = -1;
    for (int i = 0; i < size(); i++) {
        if (s->id == segments[i]->id) continue;
        if (*s < *segments[i]) continue;

        if (prev_pos < 0 || *segments[prev_pos] < *segments[i]) {
            prev_pos = i;
        }
    }
    if (prev_pos >= 0) {
        return segments[prev_pos];
    } else {
        return nullptr;
    }
}

Segment *UnorderedList::first() {
    if (size() == 0) return nullptr;

    int first_pos = 0;
    double first_y = segments[first_pos]->start->y;
    double first_x = segments[first_pos]->start->x;

    for (int i = 1; i < size(); i++) {
        double cur_y = segments[i]->y_value(first_x);
        if (cur_y < first_y) {
            first_pos = i;
            first_y = segments[first_pos]->start->y;
            first_x = segments[first_pos]->start->x;
        }
    }

    return segments[first_pos];
}

void EventContainerList::add(Event *e) {
    events.push_back(e);
}

Event *EventContainerList::pop() {
    Event *back = events.back();
    events.pop_back();
    return back;
}
int EventContainerList::size() {
    return events.size();
}

void EventContainerList::initialize() {
    // Decreasing order sort events
    sort(events.begin(), events.end(), [](Event *e1, Event *e2) {
        if (e1->x > e2->x) {
            return true;
        } else if (e1->x < e2->x) {
            return false;
        } else {
            return e1->y > e2->y;
        }
    });
}
