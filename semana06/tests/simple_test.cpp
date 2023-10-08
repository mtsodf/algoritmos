
#include <iostream>
#include <vector>

#include "data_structures.hpp"
#include "intersection_detection.h"
#include "point.h"

int main() {
    BinaryTree tree;
    int id = 0;

    Segment *s0 = new Segment(new Point(0, 0), new Point(1, 0), id++);
    tree.add(s0);

    vector<Segment *> nodes;
    tree.ordered_vec(tree.root, nodes);
    for (int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->id << " ";
    cout << endl;

    Segment *s1 = new Segment(new Point(0, 1), new Point(1, 1), id++);
    Segment *s2 = new Segment(new Point(0, -1), new Point(1, -1), id++);
    Segment *s3 = new Segment(new Point(0, -0.5), new Point(1, -0.5), id++);
    tree.add(s1);
    tree.add(s2);
    tree.add(s3);

    nodes.clear();

    tree.ordered_vec(tree.root, nodes);
    for (int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->id << " ";
    cout << endl;

    cout << "id = " << tree.next(s0)->id << endl;
    cout << "id = " << tree.next(s2)->id << endl;
    cout << "id = " << tree.next(s3)->id << endl;
    cout << "id = " << tree.next(s1) << endl;
}