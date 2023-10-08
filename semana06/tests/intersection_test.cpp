
#include <gtest/gtest.h>

#include <vector>

#include "data_structures.hpp"
#include "intersection_detection.h"
#include "point.h"

using namespace std;
// Demonstrate some basic assertions.
TEST(SegmentTests, SegmentIntersection) {
    Point a(0, 0), b(1, 1);
    Point c(1, 0), d(0, 1);
    EXPECT_TRUE(intersect(&a, &b, &c, &d));
}

TEST(SegmentTests, SegmentNotIntersection) {
    Point a(0, 0), b(1, 0);
    Point c(0, 1), d(1, 1);
    EXPECT_FALSE(intersect(&a, &b, &c, &d));
}

TEST(Intersections, NaiveIntersection) {
    vector<Point *> start, end;
    vector<pair<int, int>> intersections;
    start.push_back(new Point(0, 0));
    end.push_back(new Point(1, 1));
    start.push_back(new Point(1, 0));
    end.push_back(new Point(0, 1));

    start.push_back(new Point(1, 1));
    end.push_back(new Point(2, 2));
    start.push_back(new Point(2, 1));
    end.push_back(new Point(1, 2));

    naive_segment_intersection(start, end, intersections);
    EXPECT_EQ(intersections.size(), 2);

    EXPECT_EQ(intersections[0].first, 0);
    EXPECT_EQ(intersections[0].second, 1);

    EXPECT_EQ(intersections[1].first, 2);
    EXPECT_EQ(intersections[1].second, 3);
}

TEST(Intersections, SegmentIntersection) {
    vector<Point *> start, end;
    start.push_back(new Point(1, 1));
    end.push_back(new Point(3, 2));

    start.push_back(new Point(3.5, 3.5));
    end.push_back(new Point(5.5, 2));

    start.push_back(new Point(4, 0.5));
    end.push_back(new Point(5, 3.5));

    // Test segment_intersection with list and unordered_list
    // Iterate over all container types
    for (int i = 0; i < 2; i++) {
        string container_type = i == 0 ? "list" : "unordered_list";
        pair<int, int> intersection_pair;
        bool found = segment_intersection(start, end, intersection_pair, container_type);
        cout << "Found = " << found << endl;
        cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;
        EXPECT_EQ(intersection_pair.first, 2);
        EXPECT_EQ(intersection_pair.second, 1);
    }

    start.push_back(new Point(3.4, 1));
    end.push_back(new Point(0.5, 2));
    for (int i = 0; i < 2; i++) {
        string container_type = i == 0 ? "list" : "unordered_list";
        pair<int, int> intersection_pair;
        bool found = segment_intersection(start, end, intersection_pair, container_type);
        cout << "Found = " << found << endl;
        cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;
        EXPECT_EQ(intersection_pair.first, 0);
        EXPECT_EQ(intersection_pair.second, 3);
    }
}

TEST(Intersections, BinaryTreeTest) {
    BinaryTree tree;
    int id = 0;

    Segment *s = new Segment(new Point(0, 0), new Point(1, 0), id++);
    tree.add(s);

    vector<Segment *> nodes;
    tree.ordered_vec(tree.root, nodes);
    for (int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->id << endl;

    nodes.clear();
}