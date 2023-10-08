#include <iostream>

#include "data_structures.hpp"
#include "intersection_detection.h"

using namespace std;

void BinaryTree::add(Segment *s) {
    TreeNode *z = new TreeNode(s);
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while (x != nullptr) {
        y = x;
        if ((*z->segment) < (*x->segment)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if ((*z->segment) < (*y->segment)) {
        y->left = z;
    } else {
        y->right = z;
    }
    qtd_nodes++;
}

void BinaryTree::remove(Segment *s) {
    qtd_nodes--;
    return;
}
Segment *BinaryTree::next(Segment *s) {
    TreeNode *x = find(s);
    if (x->right != nullptr) {
        return minimum(x->right)->segment;
    }
    TreeNode *y = x->parent;
    while (y != nullptr && x->segment->id == y->right->segment->id) {
        x = y;
        y = y->parent;
    }
    if (y == nullptr) return nullptr;
    return y->segment;
}
Segment *BinaryTree::prev(Segment *s) {
    return nullptr;
}

TreeNode *BinaryTree::find(Segment *s) {
    TreeNode *x = root;
    while (x != nullptr) {
        if (s->id == x->segment->id) {
            return x;
        } else if ((*s) < (*x->segment)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return nullptr;
}

Segment *BinaryTree::get_segment(int id) {
    return nullptr;
}
void BinaryTree::swap(Segment *s1, Segment *s2) {
    return;
}

int BinaryTree::size() {
    return qtd_nodes;
}

Segment *BinaryTree::first() {
    if (root == nullptr) return nullptr;
    TreeNode *x = root;
    while (x->left != nullptr) {
        x = x->left;
    }
    return x->segment;
}

TreeNode *BinaryTree::minimum(TreeNode *x) {
    TreeNode *min = x;
    while (min->left != nullptr) {
        min = min->left;
    }
    return min;
}

void BinaryTree::ordered_vec(TreeNode *x, vector<Segment *> &segments) {
    if (x != nullptr) {
        ordered_vec(x->left, segments);
        segments.push_back(x->segment);
        ordered_vec(x->right, segments);
    }
}