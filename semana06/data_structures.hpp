#pragma once
#include <iostream>
#include <vector>

#include "event.hpp"
#include "segment.hpp"
using namespace std;

class EventContainer {
   public:
    virtual void add(Event *s) = 0;
    virtual void add_no_initialize(Event *s) = 0;
    virtual Event *pop() = 0;
    virtual int size() = 0;
    virtual void initialize() = 0;
};

class EventContainerList : public EventContainer {
   private:
    vector<Event *> events;

   public:
    EventContainerList(int n) { events.reserve(2 * n); }
    void add(Event *e);
    void add_no_initialize(Event *e);
    Event *pop();
    int size();
    void initialize();
};

class EventContainerHeap : public EventContainer {
   private:
    vector<Event *> events;

   public:
    EventContainerHeap(int n) { events.reserve(2 * n); }
    void add(Event *e);
    void add_no_initialize(Event *e);
    Event *pop();
    int size();
    void initialize();
};

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
    SegmentVector(int n) { segments.reserve(2 * n); }
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
    UnorderedList(int n) : SegmentVector(2 * n){};
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
    int height = 1;
    TreeNode(Segment *s) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        segment = s;
    };
};

class BinaryTree : public SegmentContainer {
   protected:
    int qtd_nodes;
    TreeNode *minimum(TreeNode *x);
    TreeNode *maximum(TreeNode *x);
    void transplant(TreeNode *u, TreeNode *v);

   public:
    TreeNode *root;
    TreeNode *find(Segment *s);
    BinaryTree() {
        root = nullptr;
        qtd_nodes = 0;
    }
    void add(Segment *s);
    bool update_height(TreeNode *x);
    void update_ancestors_height(TreeNode *x);
    void remove(Segment *s);
    Segment *next(Segment *s);
    TreeNode *next_node(Segment *s);
    Segment *prev(Segment *s);
    TreeNode *prev_node(Segment *s);
    Segment *get_segment(int id);
    Segment *first();
    void print(TreeNode *x, int indent = 0);
    void swap(Segment *s1, Segment *s2);
    int size();
    int count(TreeNode *x);
    int balance(TreeNode *x);
    int height(TreeNode *x);
    void ordered_vec(TreeNode *x, vector<Segment *> &segments);
    int recalculate_height(TreeNode *x);
    TreeNode *left_rotate(TreeNode *x);
    TreeNode *right_rotate(TreeNode *y);
};

class AvlTree : public BinaryTree {
   private:
   public:
    AvlTree() {
    }
    void add(Segment *s);
    TreeNode *insert(TreeNode *x, Segment *s);
    // void remove(Segment *s);
};

bool is_left_son(TreeNode *x);