
#include <gtest/gtest.h>

#include "data_structures.hpp"

TEST(AvlTree, AvlTreeTest) {
    AvlTree *tree = new AvlTree();
    int id = 0;
    double current_x = 0.5;
    Segment *s0 = new Segment(new Point(0, 0), new Point(1, 0), id++);
    s0->current_x = &current_x;
    tree->add(s0);
    vector<Segment *> nodes;

    EXPECT_EQ(tree->size(), 1);

    TreeNode *f0 = tree->find(s0);
    EXPECT_EQ(f0->segment->id, s0->id);
    EXPECT_EQ(tree->root->height, 1);

    Segment *s1 = new Segment(new Point(0, 1), new Point(1, 1), id++);
    s1->current_x = &current_x;
    tree->add(s1);
    EXPECT_EQ(tree->size(), 2);
    EXPECT_EQ(tree->root->height, 2);

    Segment *s2 = new Segment(new Point(0, 2), new Point(1, 2), id++);
    s2->current_x = &current_x;
    tree->add(s2);
    EXPECT_EQ(tree->size(), 3);
    EXPECT_EQ(tree->root->height, 2);
    return;

    Segment *s3 = new Segment(new Point(0, 3), new Point(1, 3), id++);
    s3->current_x = &current_x;
    tree->add(s3);
    EXPECT_EQ(tree->size(), 4);
    EXPECT_EQ(tree->root->height, 3);

    EXPECT_EQ(tree->root->height, 2);

    EXPECT_EQ(tree->root->right->segment->id, 2);

    // Segment *f1 = tree.find(s1);
    // EXPECT_EQ(f1->id, s1->id);

    // Segment *s2 = new Segment(new Point(0, 2), new Point(1, 2), id++);
    // s2->current_x = &current_x;
    // tree.add(s2);
    // EXPECT_EQ(tree.size(), 3);
    // Segment *f2 = tree.find(s2);
    // EXPECT_EQ(f2->id, s2->id);

    // Segment *s3 = new Segment(new Point(0, 3), new Point(1, 3), id++);
    // s3->current_x = &current_x;
    // tree.add(s3);
    // EXPECT_EQ(tree.size(), 4);
    // Segment *f3 = tree.find(s3);
    // EXPECT_EQ(f3->id, s3->id);

    // tree.remove(s2);
    // EXPECT_EQ(tree.size(), 3);

    // Segment *f4 = tree.find(s2);
    // EXPECT_EQ(f4, nullptr);

    // f1 = tree.find(s1);
    // EXPECT_EQ(f1->id, s1->id);

    // EXPECT_EQ(tree.size(), 3);

    // cout << __FUNCTION__ << __LINE__ << endl;
    // Segment *f1 = tree.find(s1);
    // EXPECT_EQ(f1->id, s1->id);
    // cout << "f1->id = " << f1->id << endl;  // "f1->id = 1

    // cout << __FUNCTION__ << __LINE__ << endl;
    // cout << __FUNCTION__ << __LINE__ << endl;
}