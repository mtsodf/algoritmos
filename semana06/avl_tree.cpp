#include <iostream>

#include "data_structures.hpp"
using namespace std;
// AVL tree implementation in C++

void AvlTree::add(Segment *s) {
    root = insert(root, s);
    qtd_nodes++;
}

TreeNode *AvlTree::insert(TreeNode *node, Segment *key) {
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)
        return new TreeNode(key);

    if (*key == *(node->segment))  // Equal keys are not allowed in BST
        return node;
    else if (*key < *(node->segment)) {
        node->left = insert(node->left, key);
        node->left->parent = node;
    } else {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance_val = balance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance_val > 1 && *key < (*node->left->segment))
        return right_rotate(node);

    // Right Right Case
    if (balance_val < -1 && *key > (*node->right->segment))
        return left_rotate(node);

    // Left Right Case
    if (balance_val > 1 && *key > (*node->left->segment)) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance_val < -1 && *key < (*node->right->segment)) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

TreeNode *AvlTree::left_rotate(TreeNode *x) {
    TreeNode *x_parent = x->parent;
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    x->parent = y;
    y->parent = x_parent;
    if (x_parent == nullptr) {
        root = y;
    }

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

    // Return new root
    return y;
}

TreeNode *AvlTree::right_rotate(TreeNode *y) {
    TreeNode *y_parent = y->parent;
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    y->parent = x;
    x->parent = y_parent;
    if (y_parent == nullptr) {
        root = x;
    }

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    // Return new root
    return x;
}
