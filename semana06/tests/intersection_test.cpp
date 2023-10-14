
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
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

    naive_segment_intersection(start, end, intersections, false);
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
    vector<string> containers = {"list", "unordered_list", "binary_tree"};
    for (int i = 0; i < containers.size(); i++) {
        string container_type = containers[i];
        vector<pair<int, int>> intersection_pairs;
        bool found = segment_intersection(start, end, intersection_pairs, container_type);
        pair<int, int> intersection_pair = intersection_pairs[0];
        cout << "Found = " << found << endl;
        cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;
        EXPECT_EQ(intersection_pair.first, 1);
        EXPECT_EQ(intersection_pair.second, 2);
    }

    start.push_back(new Point(3.4, 1));
    end.push_back(new Point(0.5, 2));
    for (int i = 0; i < containers.size(); i++) {
        string container_type = containers[i];
        vector<pair<int, int>> intersections_pair;
        pair<int, int> intersection_pair;
        bool found = segment_intersection(start, end, intersections_pair, container_type, true);
        intersection_pair = intersections_pair[0];
        cout << "Found = " << found << endl;
        cout << "Intersection Segments = " << intersection_pair.first << " " << intersection_pair.second << endl;
        EXPECT_EQ(intersection_pair.first, 0);
        EXPECT_EQ(intersection_pair.second, 3);
    }
}

TEST(Intersections, BinaryTreeTest) {
    BinaryTree tree;
    int id = 0;
    Segment *s0 = new Segment(new Point(0, 0), new Point(1, 0), id++);
    tree.add(s0);
    vector<Segment *> nodes;
    tree.ordered_vec(tree.root, nodes);

    EXPECT_EQ(tree.size(), 1);

    double current_x = 0;
    Segment *s1 = new Segment(new Point(0, 1), new Point(1, 1), id++);
    Segment *s2 = new Segment(new Point(0, -1), new Point(1, -1), id++);
    Segment *s3 = new Segment(new Point(0, -0.5), new Point(1, -0.5), id++);
    s1->current_x = &current_x;
    s2->current_x = &current_x;
    s3->current_x = &current_x;
    tree.add(s1);
    tree.add(s2);
    tree.add(s3);

    nodes.clear();

    tree.ordered_vec(tree.root, nodes);
    for (int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->id << " ";
    cout << endl;

    EXPECT_EQ(tree.prev(s1)->id, 0);
    EXPECT_EQ(tree.prev(s0)->id, 3);
    EXPECT_EQ(tree.prev(s3)->id, 2);
    EXPECT_TRUE(tree.prev(s2) == nullptr);

    EXPECT_EQ(tree.next(s0)->id, 1);
    EXPECT_EQ(tree.next(s2)->id, 3);
    EXPECT_EQ(tree.next(s3)->id, 0);
    EXPECT_TRUE(tree.next(s1) == nullptr);

    tree.remove(s3);
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(tree.next(s2)->id, 0);
    EXPECT_EQ(tree.prev(s0)->id, 2);

    nodes.clear();
}

TEST(Intersections, BinaryTreeTest2) {
    BinaryTree tree;
    int id = 0;
    int n = 1000;
    vector<Segment *> segments;
    segments.reserve(n);
    double current_x = 0.0;
    for (int i = 0; i < n; i++) {
        Segment *s = new Segment(new Point(0, i), new Point(1, i), id++);
        s->current_x = &current_x;
        segments.push_back(s);
    }

    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Shuffle segments
    shuffle(segments.begin(), segments.end(), std::default_random_engine(seed));

    for (int i = 0; i < n; i++) {
        tree.add(segments[i]);
    }

    shuffle(segments.begin(), segments.end(), std::default_random_engine(seed));

    for (int i = 0; i < n; i++) {
        tree.remove(segments[i]);
        for (int j = 0; j < i + 1; j++) {
            EXPECT_TRUE(tree.find(segments[j]) == nullptr);
        }
        for (int j = i + 1; j < n; j++) {
            EXPECT_FALSE(tree.find(segments[j]) == nullptr);
        }
        EXPECT_EQ(tree.size(), n - i - 1);
        EXPECT_EQ(tree.count(tree.root), n - i - 1);
    }

    // cout << "tree root = " << tree.root->segment->id << endl;
    // tree.print(tree.root);
}

TEST(ListInterserctions, SimpleTests) {
    vector<Segment *> segments;
    int id = 0;
    segments.push_back(new Segment(new Point(1, 1), new Point(7, 4), id++));
    segments.push_back(new Segment(new Point(2, 3), new Point(6, 1), id++));
    segments.push_back(new Segment(new Point(4, 1.5), new Point(7, 1.5), id++));

    vector<pair<int, int>> intersections;
    naive_segment_intersection(segments, intersections, false);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_TRUE(intersections[0] == make_pair<int>(0, 1));
    EXPECT_TRUE(intersections[1] == make_pair<int>(1, 2));

    intersections.clear();

    vector<string> container_types = {"list"};  //, "binary_tree"};

    for (int i = 0; i < container_types.size(); i++) {
        intersections.clear();
        segment_intersection(segments, intersections, container_types[i], "", false);
        EXPECT_EQ(intersections.size(), 2);
        EXPECT_TRUE(intersections[0] == make_pair<int>(0, 1));
        EXPECT_TRUE(intersections[1] == make_pair<int>(1, 2));
    }
}

TEST(ListSegments, NaiveComparisonExamples) {
    // Open example from relative path semana06/data/ex3.txt from ROOT_SOURCE_FOLDER
    string root_folder = ROOT_SOURCE_FOLDER;

    for (int i = 3; i <= 6; i++) {
        string example_path = root_folder + "/semana06/data/ex" + to_string(i) + ".txt";

        vector<Segment *> segments;
        read_segments_from_file(example_path, segments);

        vector<pair<int, int>> intersections_naive;
        naive_segment_intersection(segments, intersections_naive, false);

        vector<pair<int, int>> intersections_list;

        segment_intersection(segments, intersections_list, "list", "", false);

        EXPECT_EQ(intersections_naive.size(), intersections_list.size());

        sort(intersections_naive.begin(), intersections_naive.end());
        sort(intersections_list.begin(), intersections_list.end());

        for (int i = 0; i < intersections_naive.size(); i++) {
            EXPECT_EQ(intersections_naive[i].first, intersections_list[i].first);
            EXPECT_EQ(intersections_naive[i].second, intersections_list[i].second);
        }
    }
}
TEST(ListSegments, NaiveComparisonRandom) {
    // Open example from relative path semana06/data/ex3.txt from ROOT_SOURCE_FOLDER
    string root_folder = ROOT_SOURCE_FOLDER;

    for (int i = 0; i < 10000; i++) {
        vector<Segment *> segments;
        generate_segments(10, 0.5, 0.05, segments);

        vector<pair<int, int>> intersections_naive;
        naive_segment_intersection(segments, intersections_naive, false);

        vector<pair<int, int>> intersections_list;

        segment_intersection(segments, intersections_list, "list", "", false);

        EXPECT_EQ(intersections_naive.size(), intersections_list.size());

        if (intersections_naive.size() != intersections_list.size()) {
            cout << "Naive size = " << intersections_naive.size() << endl;
            cout << "List size = " << intersections_list.size() << endl;
            fstream segments_file;
            segments_file.open("segments_error.txt", ios::out);
            for (int i = 0; i < segments.size(); i++) {
                segments_file << segments[i]->start->x << " " << segments[i]->start->y << " " << segments[i]->end->x << " " << segments[i]->end->y << "\n";
            }
            segments_file.close();

            return;
        }

        sort(intersections_naive.begin(), intersections_naive.end());
        sort(intersections_list.begin(), intersections_list.end());

        for (int i = 0; i < intersections_naive.size(); i++) {
            EXPECT_EQ(intersections_naive[i].first, intersections_list[i].first);
            EXPECT_EQ(intersections_naive[i].second, intersections_list[i].second);
        }

        for (int i = 0; i < segments.size(); i++) {
            delete segments[i];
        }
    }
}