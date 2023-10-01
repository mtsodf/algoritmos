#include <iostream>
#include <vector>

#include "point.h"
#include "points_triangulation.h"
#include "random_points.h"

using namespace std;

int main() {
    vector<vector<int>> triangles_benchmark;

    triangles_benchmark.push_back({0, 1, 2});
    triangles_benchmark.push_back({0, 2, 3});

    vector<vector<int>> adjacency_list_benchmark;

    adjacency_list_benchmark.push_back({-1, 1, -1});
    adjacency_list_benchmark.push_back({-1, -1, 0});

    vector<double> xs;
    vector<double> ys;
    generate_regular_polygon(4, xs, ys);
    vector<int> points_int = {0, 1, 2, 3};

    for (int i = 0; i < xs.size(); i++) {
        cout << xs[i] << " " << ys[i] << endl;
    }

    vector<Point *> points;
    for (int i = 0; i < xs.size(); i++) {
        points.push_back(new Point(xs[i], ys[i]));
    }

    vector<vector<int>> triangles;
    vector<vector<int>> adjacency_list;
    triangulate_convex_polygon(points_int, triangles, adjacency_list);
    write_triangulation_json(&points, &triangles, &adjacency_list, -1.0, "triangulation.json");

    // Compare triangles benchmark with triangles
    for (int i = 0; i < triangles_benchmark.size(); i++) {
        for (int j = 0; j < triangles_benchmark[i].size(); j++) {
            if (triangles_benchmark[i][j] != triangles[i][j]) {
                cout << "triangles_benchmark[" << i << "][" << j << "] = " << triangles_benchmark[i][j] << endl;
                cout << "triangles[" << i << "][" << j << "] = " << triangles[i][j] << endl;
                cout << "triangles_benchmark != triangles" << endl;
                return 1;
            }
        }
    }

    // Compare adjacency_list_benchmark with adjacency_list
    for (int i = 0; i < adjacency_list_benchmark.size(); i++) {
        for (int j = 0; j < adjacency_list_benchmark[i].size(); j++) {
            if (adjacency_list_benchmark[i][j] != adjacency_list[i][j]) {
                cout << "adjacency_list_benchmark[" << i << "][" << j << "] = " << adjacency_list_benchmark[i][j] << endl;
                cout << "adjacency_list[" << i << "][" << j << "] = " << adjacency_list[i][j] << endl;
                cout << "adjacency_list_benchmark != adjacency_list" << endl;
                return 1;
            }
        }
    }

    return 0;
}