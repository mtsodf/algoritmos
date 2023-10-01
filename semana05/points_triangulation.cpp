#include "points_triangulation.h"

#include <fstream>
#include <iostream>
#include <string>

#include "graham.h"
#include "point.h"
#include "polygon.h"
#include "utilities.h"

using namespace std;

void change_value(vector<int> &vec, int old_value, int new_value) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == old_value) {
            vec[i] = new_value;
            return;
        }
    }
}

void triangulate_trig(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list) {
    vector<int> *convex_hull;
    convex_hull = graham(points, "std");
    int h = convex_hull->size();
    // pi t = pi*(h-2) + 2*pi*(n-h)
    // t = h - 2 + 2n -2h = 2n - h - 2
    int qtd_triangles = 2 * points->size() - h - 2;
    triangles.reserve(qtd_triangles);
    adjacency_list.reserve(qtd_triangles);
    triangulate_convex_polygon(*convex_hull, triangles, adjacency_list);

    cout << __FILE__ << ":" << __LINE__ << endl;
    vector<bool> triangulated(points->size(), false);
    for (int i = 0; i < convex_hull->size(); i++) {
        triangulated[(*convex_hull)[i]] = true;
    }
    cout << __FILE__ << ":" << __LINE__ << endl;

    Polygon *poligon = new Polygon(points, convex_hull);
    vector<int> *tpoints = new vector<int>(3);

    for (int i = 0; i < points->size(); i++) {
        if (!triangulated[i]) {
            for (int t_int = 0; t_int < triangles.size(); t_int++) {
                int a_index = triangles[t_int][0];
                int b_index = triangles[t_int][1];
                int c_index = triangles[t_int][2];
                (*tpoints) = {a_index, b_index, c_index};
                poligon->vert_list = tpoints;
                if (poligon->point_inside((*points)[i]->x, (*points)[i]->y)) {
                    triangles[t_int][2] = i;
                    // New triangle indexes
                    int t_ab = t_int;
                    int t_bc = adjacency_list.size();
                    int t_ac = adjacency_list.size() + 1;

                    // Adjacent triangles
                    int adj_ab = adjacency_list[t_int][2];
                    int adj_ac = adjacency_list[t_int][1];
                    int adj_bc = adjacency_list[t_int][0];

                    adjacency_list[t_ab][0] = t_bc;
                    adjacency_list[t_ab][1] = t_ac;

                    triangles.push_back({b_index, c_index, i});
                    adjacency_list.push_back({t_ac, t_ab, adj_bc});
                    if (adj_bc != -1) {
                        change_value(adjacency_list[adj_bc], t_int, t_bc);
                    }

                    triangles.push_back({c_index, a_index, i});
                    adjacency_list.push_back({t_ab, t_bc, adj_ac});
                    if (adj_ac != -1) {
                        change_value(adjacency_list[adj_ac], t_int, t_ac);
                    }

                    break;
                }
            }
        }
    }
}

void triangulate_convex_polygon(vector<int> &points_int, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list) {
    int n = points_int.size();
    int qtd_triangles = n - 2;

    for (int i = 0; i < qtd_triangles; i++) {
        triangles.push_back({0, points_int[i + 1], points_int[i + 2]});
        adjacency_list.push_back({-1, -1, -1});
        adjacency_list[i][0] = -1;
        if (i < qtd_triangles - 1) {
            adjacency_list[i][1] = i + 1;
        }
        if (i > 0) {
            adjacency_list[i][2] = i - 1;
        }
    }
}

void write_triangulation_json(vector<Point *> *points, vector<vector<int>> *triangles, vector<vector<int>> *adjacency_list, string alg, double time_seconds, string filename) {
    fstream output;
    output.open(filename, ios::out);
    output << "{\n";
    output << "\"n\": " << points->size() << ",\n";
    output << "\"time\":" << std::scientific << std::setprecision(8) << time_seconds << ",\n";
    output << "\"algorithm\": \"" << alg << "\",\n";
    write_points_on_json(output, *points);
    output << ",\n";
    write_int_matrix_on_json(output, *triangles, "triangles");
    output << ",\n";
    write_int_matrix_on_json(output, *adjacency_list, "adjacency_list");
    output << "}\n";
    output.close();
}