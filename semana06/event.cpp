
#include "event.hpp"

#include "segment.hpp"

Event::Event(Segment *seg, Segment *other_seg, int type, double x, double y) {
    this->seg = seg;
    this->other_seg = other_seg;
    this->type = type;

    if (type == SEGMENT_START) {
        this->x = seg->start->x;
        this->y = seg->start->y;
    } else if (type == SEGMENT_END) {
        this->x = seg->end->x;
        this->y = seg->end->y;
    } else {
        this->x = x;
        this->y = y;
    }
}
// override comparison operator <
bool Event::operator<(const Event &other) const {
    if (this->x < other.x) {
        return true;
    } else if (this->x > other.x) {
        return false;
    } else {
        return this->y < other.y;
    }
}