#include "points_triangulation.h"

#include <fstream>
#include <string>

#include "graham.h"
#include "point.h"
#include "polygon.h"
#include "utilities.h"

using namespace std;

void triangulate_trig(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list) {
    vector<int> *convex_hull = graham(points, "std");
    int h = convex_hull->size();
    // pi t = pi*(h-2) + 2*pi*(n-h)
    // t = h - 2 + 2n -2h = n - h - 2
    int qtd_triangles = points->size() - h - 2;
    triangles.reserve(qtd_triangles);
    adjacency_list.reserve(qtd_triangles);
    triangulate_convex_polygon(*convex_hull, triangles, adjacency_list);
}

void triangulate_convex_polygon(vector<int> &points_int, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list) {
    int n = points_int.size();
    int qtd_triangles = n - 2;

    for (int i = 0; i < qtd_triangles; i++) {
        triangles.push_back({0, points_int[i + 1], points_int[i + 2]});
        adjacency_list.push_back({-1, -1, -1});
        adjacency_list[i][0] = -1;
        if (i < qtd_triangles - 1) {
            adjacency_list[i][1] = points_int[i + 1];
        }
        if (i > 0) {
            adjacency_list[i][2] = points_int[i - 1];
        }
    }
}

void write_triangulation_json(vector<Point *> *points, vector<vector<int>> *triangles, vector<vector<int>> *adjacency_list, string filename) {
    fstream output;
    output.open(filename, ios::out);
    output << "{\n";

    output << "\"n\": " << points->size() << ",\n";
    write_points_on_json(output, *points);
    output << ",\n";
    write_int_matrix_on_json(output, *triangles, "triangles");
    output << ",\n";
    write_int_matrix_on_json(output, *adjacency_list, "adjacency_list");

    output << "}\n";
    output.close();
}