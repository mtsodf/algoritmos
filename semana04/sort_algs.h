#pragma once
#include <vector>

#include "point.h"

using namespace std;

// Add a sort function that receives a comparator
void selection_sort(vector<Point *> *points, int init, int end, function<bool(Point *, Point *)> comparator) {
    for (int i = init; i < end; i++) {
        int min = i;
        for (int j = i + 1; j < end; j++) {
            if (comparator((*points)[j], (*points)[min])) {
                min = j;
            }
        }
        swap(*(*points)[i], *(*points)[min]);
    }
}

void heap_sort(vector<Point *> *points, int init, int end, function<bool(Point *, Point *)> comparator) {
    vector<Point *> heap_points;
    heap_points.reserve(points->size());
    make_heap(heap_points.begin(), heap_points.end(), comparator);

    for (int i = init; i < end; i++) {
        heap_points.push_back((*points)[i]);
        push_heap(heap_points.begin(), heap_points.end(), comparator);
    }

    for (int i = end - 1; i >= init; i--) {
        Point *next_point = heap_points.front();
        pop_heap(heap_points.begin(), heap_points.end(), comparator);
        heap_points.pop_back();
        (*points)[i] = next_point;
    }
}
