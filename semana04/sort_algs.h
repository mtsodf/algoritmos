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

void insertion_sort(vector<Point *> *points, int init, int end, function<bool(Point *, Point *)> comparator) {
    for (int i = 1; i < points->size(); i++) {
        for (int j = i; j >= 1; j--) {
            if (comparator((*points)[j], (*points)[j - 1])) {
                swap(*(*points)[j], *(*points)[j - 1]);
            }
        }
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

void quick_sort(vector<Point *> *points, int init, int end, function<bool(Point *, Point *)> comparator) {
    if (init >= end) return;
    int pivot_pos = init;
    for (int i = init; i < end; i++) {
        if (comparator((*points)[i], (*points)[pivot_pos])) {
            swap(*(*points)[i], *(*points)[pivot_pos]);
            swap(*(*points)[pivot_pos + 1], *(*points)[i]);
            pivot_pos = pivot_pos + 1;
        }
    }
    quick_sort(points, init, pivot_pos, comparator);
    quick_sort(points, pivot_pos + 1, end, comparator);
}