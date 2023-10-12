#include <iomanip>
#include <iostream>

#include "data_structures.hpp"
#include "intersection_detection.h"

#define debug cout << __FUNCTION__ << " " << __LINE__ << endl;
#define debug ;

using namespace std;

bool is_left_son(TreeNode *x) {
    if (x == nullptr) return false;
    TreeNode *parent = x->parent;
    if (parent == nullptr || parent->left == nullptr) return false;

    return x->segment->id == parent->left->segment->id;
}

bool is_right_son(TreeNode *x) {
    if (x == nullptr) return false;
    TreeNode *parent = x->parent;
    if (parent == nullptr || parent->right == nullptr) return false;

    return x->segment->id == parent->right->segment->id;
}

void BinaryTree::add(Segment *s) {
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
}

void BinaryTree::remove(Segment *s) {
    TreeNode *z = find(s);
    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        TreeNode *y = minimum(z->right);
        // TODO olhar comparação
        if ((y->parent != nullptr) && y->parent->segment->id != z->segment->id) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
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

TreeNode *BinaryTree::next_node(Segment *s) {
    TreeNode *x = find(s);
    if (x->right != nullptr) {
        return minimum(x->right);
    }
    TreeNode *y = x->parent;
    while (y != nullptr && is_right_son(x)) {
        x = y;
        y = y->parent;
    }
    if (y == nullptr) return nullptr;
    return y;
}
Segment *BinaryTree::next(Segment *s) {
    TreeNode *x = next_node(s);
    if (x == nullptr) return nullptr;
    return x->segment;
}

TreeNode *BinaryTree::prev_node(Segment *s) {
    if (s == nullptr) return nullptr;
    TreeNode *x = find(s);
    if (x == nullptr) {
        cout << "Segment not found" << endl;
        cout << "id = " << s->id << endl;
        cout << "size = " << qtd_nodes << endl;
        // Kill program
        exit(1);
    }
    if (x->left != nullptr) return maximum(x->left);

    TreeNode *y = x->parent;
    while (y != nullptr && is_left_son(x)) {
        x = y;
        y = y->parent;
    }
    if (y == nullptr) return nullptr;
    return y;
}

Segment *BinaryTree::prev(Segment *s) {
    TreeNode *x = prev_node(s);
    if (x == nullptr) return nullptr;
    return x->segment;
}

TreeNode *BinaryTree::find(Segment *s) {
    TreeNode *x = root;
    while (x != nullptr) {
        if (s->id == x->segment->id) {
            return x;
        } else if (*(s) < *(x->segment)) {
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
    return minimum(root)->segment;
}

TreeNode *BinaryTree::minimum(TreeNode *x) {
    TreeNode *min = x;
    while (min->left != nullptr) {
        min = min->left;
    }
    return min;
}

TreeNode *BinaryTree::maximum(TreeNode *x) {
    TreeNode *max = x;
    while (max->right != nullptr) {
        max = max->right;
    }
    return max;
}

void BinaryTree::ordered_vec(TreeNode *x, vector<Segment *> &segments) {
    if (x != nullptr) {
        ordered_vec(x->left, segments);
        segments.push_back(x->segment);
        ordered_vec(x->right, segments);
    }
}

void BinaryTree::print(TreeNode *x, int indent) {
    if (x != nullptr) {
        if (x->right != nullptr) {
            print(x->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (x->right != nullptr) std::cout << " /\n"
                                           << std::setw(indent) << ' ';
        std::cout << x->segment->id << "\n ";
        if (x->left != nullptr) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            print(x->left, indent + 4);
        }
    }
}

void BinaryTree::transplant(TreeNode *u, TreeNode *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (is_left_son(u)) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

int BinaryTree::count(TreeNode *x) {
    if (x == nullptr) return 0;

    return 1 + count(x->left) + count(x->right);
}