#include <iostream>

#include "points_triangulation.h"
#include "polygon.h"
#include "random_points.h"
#include "utilities.h"

int main() {
    vector<double> xs;
    vector<double> ys;
    // read_polygon_from_file("../../semana05/data/test_0.txt", xs, ys, false);
    generate_regular_polygon(10, xs, ys);

    vector<Point *> *points = new vector<Point *>;

    for (int i = 0; i < xs.size(); i++) {
        points->push_back(new Point(xs[i], ys[i]));
    }

    vector<vector<int>> triangles;
    vector<vector<int>> adjacency_list;
    triangulate_trig(points, triangles, adjacency_list);

    write_triangulation_json(points, &triangles, &adjacency_list, "triangulation.json");
}