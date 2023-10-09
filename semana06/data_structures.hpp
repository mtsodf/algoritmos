#pragma once
#include "intersection_detection.h"
// Create abstract class of container of segments
class SegmentContainer {
   public:
    virtual void add(Segment *s) = 0;
    virtual void remove(Segment *s) = 0;
    virtual Segment *next(Segment *s) = 0;
    virtual Segment *prev(Segment *s) = 0;
    // virtual Segment *get_segment(int id) = 0;
    virtual Segment *first() = 0;
    virtual void swap(Segment *s1, Segment *s2) = 0;
    virtual int size() = 0;
};

class SegmentVector : public SegmentContainer {
   protected:
    vector<Segment *> segments;

   public:
    SegmentVector() {}
    void add(Segment *s);
    void remove(Segment *s);
    Segment *next(Segment *s);
    Segment *prev(Segment *s);
    Segment *get_segment(int id);
    Segment *first();
    void swap(Segment *s1, Segment *s2);
    int size();
    int find_pos(Segment *s);
};

class UnorderedList : public SegmentVector {
   private:
   public:
    UnorderedList() {}
    void add(Segment *s);
    Segment *next(Segment *s);
    Segment *prev(Segment *s);
    Segment *first();
};

class TreeNode {
   public:
    Segment *segment;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(Segment *s) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        segment = s;
    };
};

class BinaryTree : public SegmentContainer {
   private:
    int qtd_nodes;
    TreeNode *find(Segment *s);
    TreeNode *minimum(TreeNode *x);
    TreeNode *maximum(TreeNode *x);
    void transplant(TreeNode *u, TreeNode *v);

   public:
    TreeNode *root;
    BinaryTree() {
        root = nullptr;
        qtd_nodes = 0;
    }
    void add(Segment *s);
    void remove(Segment *s);
    Segment *next(Segment *s);
    TreeNode *next_node(Segment *s);
    Segment *prev(Segment *s);
    TreeNode *prev_node(Segment *s);
    Segment *get_segment(int id);
    Segment *first();
    void print(TreeNode *x);
    void swap(Segment *s1, Segment *s2);
    int size();
    void ordered_vec(TreeNode *x, vector<Segment *> &segments);
};