#include "data_structures.hpp"

#include "intersection_detection.h"

// Add Implementation with vector
class SegmentVector : public SegmentContainer {
   private:
    vector<Segment *> segments;

   public:
    SegmentVector() {}
    void add(Segment *s) {
        double cur_y = s->start->y;
        double cur_x = s->start->x;

        segments.push_back(s);
        int seg_pos;
        for (seg_pos = segments.size() - 1; seg_pos >= 1; seg_pos--) {
            if (cur_y > segments[seg_pos - 1]->y_value(cur_x)) {
                swap(segments[seg_pos], segments[seg_pos - 1]);
            } else {
                break;
            }
        }
    }

    int find_pos(Segment *s) {
        int seg_pos = -1;
        for (seg_pos = 0; seg_pos < segments.size(); seg_pos++) {
            if (s->id == segments[seg_pos]->id) break;
        }
        return seg_pos;
    }

    void remove(Segment *s) {
        int seg_pos = find_pos(s);

        for (int j = seg_pos; j < segments.size() - 1; j++) {
            swap(segments[j], segments[j + 1]);
        }

        segments.pop_back();
    }
    Segment *next(Segment *s) {
        int pos = find_pos(s);
        if (pos < segments.size() - 1) {
            return segments[pos + 1];
        } else {
            return nullptr;
        }
    }
    Segment *prev(Segment *s) {
        int pos = find_pos(s);
        if (pos > 0) {
            return segments[pos - 1];
        } else {
            return nullptr;
        }
    }

    Segment *get_segment(int id) {
        for (int i = 0; i < segments.size(); i++) {
            if (segments[i]->id == id) {
                return segments[i];
            }
        }
        return nullptr;
    }
    void swap(Segment *s1, Segment *s2) {
        for (int i = 0; i < segments.size(); i++) {
            if (segments[i]->id == s1->id) {
                segments[i] = s2;
            } else if (segments[i]->id == s2->id) {
                segments[i] = s1;
            }
        }
    }
    int size() { return segments.size(); }
};