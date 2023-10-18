#include <iostream>

#include "data_structures.hpp"
using namespace std;
// AVL tree implementation in C++

void AvlTree::add(Segment *s) {
    TreeNode *z = new TreeNode(s);
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while (x != nullptr) {
        y = x;
        if (*(z->segment) < *(x->segment)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (*(z->segment) < *(y->segment)) {
        y->left = z;
    } else {
        y->right = z;
    }
    qtd_nodes++;
    TreeNode *p = z;
    while (p != nullptr) {
        update_height(p);
        int balance_value = balance(p);
        if (balance_value > 1) {
            if (balance(p->left) >= 0) {
                p = right_rotate(p);
            } else {
                p->left = left_rotate(p->left);
                p = right_rotate(p);
            }
        } else if (balance_value < -1) {
            if (balance(p->right) <= 0) {
                p = left_rotate(p);
            } else {
                p->right = right_rotate(p->right);
                p = left_rotate(p);
            }
        }
        p = p->parent;
    }
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

void AvlTree::remove(Segment *s) {
    TreeNode *z = find(s);
    TreeNode *w = z->parent;
    if (z->left == nullptr) {
        transplant(z, z->right);
        update_ancestors_height(z->parent);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
        update_ancestors_height(z->parent);
    } else {
        TreeNode *y = minimum(z->right);
        // TODO olhar comparação
        TreeNode *y_parent = nullptr;
        if ((y->parent != nullptr) && y->parent->segment->id != z->segment->id) {
            y_parent = y->parent;
            w = y->parent;
            transplant(y, y->right);
            TreeNode *y_right = y->right;
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        update_ancestors_height(y);
        update_ancestors_height(y_parent);

        while (w != nullptr) {
            update_height(w);
            int balance_value = balance(w);
            if (balance_value > 1) {
                if (balance(w->left) >= 0) {
                    w = right_rotate(w);
                } else {
                    w->left = left_rotate(w->left);
                    w = right_rotate(w);
                }
            } else if (balance_value < -1) {
                if (balance(w->right) <= 0) {
                    w = left_rotate(w);
                } else {
                    w->right = right_rotate(w->right);
                    w = left_rotate(w);
                }
            }
            w = w->parent;
        }
    }
    qtd_nodes--;

#ifdef DEBUG
    if (count(root) != qtd_nodes) {
        cout << "ERROR REMOVING NODE = " << s->id << endl;
        exit(1);
    }
#endif

    return;
}

TreeNode *BinaryTree::left_rotate(TreeNode *x) {
    if (x == nullptr || x->right == nullptr) return nullptr;
    bool x_is_left_son = is_left_son(x);
    TreeNode *x_parent = x->parent;
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;
    if (T2 != nullptr) T2->parent = x;

    x->parent = y;
    y->parent = x_parent;
    if (x_parent == nullptr) {
        root = y;

    } else {
        if (x_is_left_son) {
            x_parent->left = y;
        } else {
            x_parent->right = y;
        }
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

TreeNode *BinaryTree::right_rotate(TreeNode *y) {
    if (y == nullptr || y->left == nullptr) return nullptr;
    bool y_is_left_son = is_left_son(y);
    TreeNode *y_parent = y->parent;
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;
    if (T2 != nullptr) T2->parent = y;

    y->parent = x;
    x->parent = y_parent;
    if (y_parent == nullptr) {
        root = x;
    } else {
        if (y_is_left_son) {
            y_parent->left = x;
        } else {
            y_parent->right = x;
        }
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
