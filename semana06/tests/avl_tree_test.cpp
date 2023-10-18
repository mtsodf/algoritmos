#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include "data_structures.hpp"

using namespace std;

TEST(BinaryTree, LeftRotationsTest) {
    BinaryTree *tree = new BinaryTree();
    int id = 0;
    double current_x = 0.5;

    for (int i = 0; i < 3; i++) {
        Segment *s = new Segment(new Point(0, i), new Point(1, i), id++);
        s->current_x = &current_x;
        tree->add(s);
    }

    tree->left_rotate(tree->root);

    EXPECT_EQ(tree->root->segment->id, 1);
    EXPECT_EQ(tree->root->left->segment->id, 0);
    EXPECT_EQ(tree->root->right->segment->id, 2);
}

TEST(BinaryTree, HeightTrackTest) {
    BinaryTree *tree = new BinaryTree();
    BinaryTree *ref_tree = new BinaryTree();
    double current_x = 0.5;
    int id = 0;
    int n = 10;
    vector<int> order;

    for (int i = 0; i < n; i++) {
        order.push_back(i);
    }

    for (int cases = 0; cases < 100; cases++) {
        vector<Segment *> segments;
        for (int i = 0; i < n; i++) {
            Segment *s = new Segment(new Point(0, i), new Point(1, i), id++);
            s->current_x = &current_x;
            segments.push_back(s);
        }

        // shuffle segments
        shuffle(order.begin(), order.end(), mt19937(random_device()()));

        for (int i = 0; i < n; i++) {
            Segment *s = segments[order[i]];
            tree->add(s);
            ref_tree->add(s);
        }

        ref_tree->recalculate_height(ref_tree->root);

        for (int i = 0; i < n; i++) {
            EXPECT_EQ(tree->find(segments[i])->height, ref_tree->find(segments[i])->height);
        }

        shuffle(segments.begin(), segments.end(), mt19937(random_device()()));
        for (int i = 0; i < n - 1; i++) {
            tree->remove(segments[order[i]]);
            ref_tree->remove(segments[order[i]]);
            ref_tree->recalculate_height(ref_tree->root);
            for (int j = i + 1; j < n; j++)
                EXPECT_EQ(tree->find(segments[order[j]])->height, ref_tree->find(segments[order[j]])->height);
        }
    }
}

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
    EXPECT_EQ(tree->root->segment->id, 1);
    EXPECT_TRUE(tree->root->parent == nullptr);
    EXPECT_EQ(tree->root->left->segment->id, 0);
    EXPECT_EQ(tree->root->left->parent->segment->id, 1);
    EXPECT_EQ(tree->root->right->segment->id, 2);
    EXPECT_EQ(tree->root->right->parent->segment->id, 1);

    Segment *s3 = new Segment(new Point(0, 3), new Point(1, 3), id++);
    s3->current_x = &current_x;
    tree->add(s3);
    EXPECT_EQ(tree->size(), 4);
    EXPECT_EQ(tree->root->height, 3);
    EXPECT_EQ(tree->root->segment->id, 1);
    EXPECT_EQ(tree->root->left->segment->id, 0);
    EXPECT_EQ(tree->root->right->segment->id, 2);
    EXPECT_EQ(tree->root->right->right->segment->id, 3);

    Segment *s4 = new Segment(new Point(0, 4), new Point(1, 4), id++);
    s4->current_x = &current_x;
    tree->add(s4);
    EXPECT_EQ(tree->size(), 5);
    EXPECT_EQ(tree->root->height, 3);
    EXPECT_EQ(tree->root->segment->id, 1);
    EXPECT_EQ(tree->root->left->segment->id, 0);
    EXPECT_EQ(tree->root->right->segment->id, 3);
    EXPECT_EQ(tree->root->right->right->segment->id, 4);
    EXPECT_EQ(tree->root->right->left->segment->id, 2);

    Segment *s5 = new Segment(new Point(0, 5), new Point(1, 5), id++);
    s5->current_x = &current_x;
    tree->add(s5);
    EXPECT_EQ(tree->size(), 6);
    EXPECT_EQ(tree->root->height, 3);
    EXPECT_EQ(tree->root->segment->id, 3);
    EXPECT_EQ(tree->root->left->segment->id, 1);
    EXPECT_EQ(tree->root->left->left->segment->id, 0);
    EXPECT_EQ(tree->root->left->right->segment->id, 2);
    EXPECT_EQ(tree->root->right->segment->id, 4);
    EXPECT_EQ(tree->root->right->right->segment->id, 5);
}

TEST(AvlTree, AvlTreeTest2) {
    AvlTree *tree = new AvlTree();
    double current_x = 0.5;
    Segment *s0 = new Segment(new Point(0, 0), new Point(1, 0), 0);
    s0->current_x = &current_x;
    tree->add(s0);
    vector<Segment *> nodes;

    EXPECT_EQ(tree->size(), 1);

    Segment *s1 = new Segment(new Point(0, 2), new Point(1, 2), 2);
    s1->current_x = &current_x;
    tree->add(s1);
    EXPECT_EQ(tree->size(), 2);
    EXPECT_EQ(tree->root->height, 2);

    Segment *s2 = new Segment(new Point(0, 1), new Point(1, 1), 1);
    s2->current_x = &current_x;
    tree->add(s2);
    EXPECT_EQ(tree->size(), 3);
    EXPECT_EQ(tree->root->height, 2);
    EXPECT_EQ(tree->root->segment->id, 1);
    EXPECT_TRUE(tree->root->parent == nullptr);
    EXPECT_EQ(tree->root->left->segment->id, 0);
    EXPECT_EQ(tree->root->left->parent->segment->id, 1);
    EXPECT_EQ(tree->root->right->segment->id, 2);
    EXPECT_EQ(tree->root->right->parent->segment->id, 1);
}
TEST(AvlTree, AvlTreeTest3) {
    AvlTree *tree = new AvlTree();
    double current_x = 0.5;
    vector<Segment *> segments;
    int n = 1023;
    for (int i = 0; i < n; i++) {
        Segment *s = new Segment(new Point(0, i), new Point(1, i), segments.size());
        s->current_x = &current_x;
        segments.push_back(s);
    }

    shuffle(segments.begin(), segments.end(), mt19937(random_device()()));
    for (int i = 0; i < segments.size(); i++) {
        tree->add(segments[i]);
    }

    for (int i = 0; i < segments.size(); i++) {
        TreeNode *node = tree->find(segments[i]);
        EXPECT_TRUE(node != nullptr);
        EXPECT_EQ(node->segment->id, segments[i]->id);
    }

    cout << "tree size: " << tree->size() << endl;
    cout << "tree depth: " << tree->root->height << endl;
}
