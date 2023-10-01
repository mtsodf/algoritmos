#include "points_triangulation.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "graham.h"
#include "point.h"
#include "polygon.h"
#include "utilities.h"

using namespace std;

// Custom hash function for Pair
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

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

void write_triangulation_json(vector<Point *> *points, vector<vector<int>> *triangles, vector<vector<int>> *adjacency_list, string alg, double time_seconds, vector<int> &path, string filename) {
    fstream output;
    output.open(filename, ios::out);
    output << "{\n";
    output << "\"n\": " << points->size() << ",\n";
    output << "\"time\":" << std::scientific << std::setprecision(8) << time_seconds << ",\n";
    output << "\"algorithm\": \"" << alg << "\",\n";
    output << "\"path\": [";
    for (int i = 0; i < path.size(); i++) {
        output << path[i];
        if (i < path.size() - 1) {
            output << ", ";
        }
    }
    output << "],\n";
    write_points_on_json(output, *points);
    output << ",\n";
    write_int_matrix_on_json(output, *triangles, "triangles");
    output << ",\n";
    write_int_matrix_on_json(output, *adjacency_list, "adjacency_list");
    output << "}\n";
    output.close();
}

void correct_adjacency_list(vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list, unordered_map<pair<int, int>, int, pair_hash> &edges_triangles, int cur_triangle) {
    adjacency_list.push_back({-1, -1, -1});
    for (int a = 2, b = 0; b < 3; a = b, b++) {
        // int edge_triangle = edges_triangles[triangles[cur_triangle][a]][triangles[cur_triangle][b]];

        pair<int, int> edge = make_pair(triangles[cur_triangle][a], triangles[cur_triangle][b]);
        auto it = edges_triangles.find(edge);

        if (it != edges_triangles.end()) {
            int edge_triangle = edges_triangles[edge];
            if (b == 0) adjacency_list[cur_triangle][1] = edge_triangle;
            if (b == 1) adjacency_list[cur_triangle][2] = edge_triangle;
            if (b == 2) adjacency_list[cur_triangle][0] = edge_triangle;

            for (int i = 0; i < 3; i++) {
                int v1 = triangles[edge_triangle][i], v2 = triangles[edge_triangle][(i + 1) % 3];
                int v3 = triangles[cur_triangle][a], v4 = triangles[cur_triangle][b];
                if ((v1 == v3 && v2 == v4) || (v1 == v4 && v2 == v3)) {
                    if (i == 0) adjacency_list[edge_triangle][2] = cur_triangle;
                    if (i == 1) adjacency_list[edge_triangle][0] = cur_triangle;
                    if (i == 2) adjacency_list[edge_triangle][1] = cur_triangle;
                }
            }

        } else {
            edges_triangles[make_pair(triangles[cur_triangle][a], triangles[cur_triangle][b])] = cur_triangle;
            edges_triangles[make_pair(triangles[cur_triangle][b], triangles[cur_triangle][a])] = cur_triangle;
        }
    }
}

void triangulate_graham(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list) {
    int init_point = get_min_point_index(*points);

    Point *base_point = (*points)[init_point];

    // Put init_point at the beginning of the vector
    Point *temp = (*points)[0];
    (*points)[0] = (*points)[init_point];
    (*points)[init_point] = temp;

    cout << "Base point = " << base_point->x << ", " << base_point->y << endl;

    function<bool(Point *, Point *)> comparator = [&base_point](Point *a, Point *b) {
        return ccw_or_collinear(base_point, a, b);
    };

    // Sort beggining from second element
    sort(begin(*points) + 1, end(*points), comparator);

    vector<int> *convex_hull = new vector<int>;
    convex_hull->reserve(points->size());
    convex_hull->push_back(0);
    convex_hull->push_back(1);
    convex_hull->push_back(2);

    triangles.reserve(2 * points->size() - 1);
    adjacency_list.reserve(2 * points->size() - 1);

    triangles.push_back({0, 1, 2});
    adjacency_list.push_back({-1, -1, -1});

    // vector<vector<int>> *edges_triangles = new vector<vector<int>>(points->size(), vector<int>(points->size(), -1));
    // (*edges_triangles)[0][1] = 0;
    // (*edges_triangles)[1][0] = 0;
    // (*edges_triangles)[1][2] = 0;
    // (*edges_triangles)[2][1] = 0;
    // (*edges_triangles)[0][2] = 0;
    // (*edges_triangles)[2][0] = 0;
    unordered_map<pair<int, int>, int, pair_hash> *edges_triangles = new unordered_map<pair<int, int>, int, pair_hash>;
    (*edges_triangles)[make_pair(0, 1)] = 0;
    (*edges_triangles)[make_pair(1, 0)] = 0;
    (*edges_triangles)[make_pair(1, 2)] = 0;
    (*edges_triangles)[make_pair(2, 1)] = 0;
    (*edges_triangles)[make_pair(0, 2)] = 0;
    (*edges_triangles)[make_pair(2, 0)] = 0;

    Point *point_a, *point_b;
    for (int i = 3; i < points->size(); i++) {
        point_a = (*points)[(*convex_hull)[convex_hull->size() - 2]];
        point_b = (*points)[(*convex_hull)[convex_hull->size() - 1]];

        int a = 0;
        int b = (*convex_hull)[convex_hull->size() - 1];
        int c = i;
        triangles.push_back({a, b, c});
        int cur_triangle = triangles.size() - 1;
        correct_adjacency_list(triangles, adjacency_list, *edges_triangles, cur_triangle);

        while (!ccw_or_collinear(point_a, point_b, (*points)[i])) {
            triangles.push_back({(*convex_hull)[convex_hull->size() - 2], (*convex_hull)[convex_hull->size() - 1], i});
            cur_triangle = triangles.size() - 1;
            correct_adjacency_list(triangles, adjacency_list, *edges_triangles, cur_triangle);
            convex_hull->pop_back();
            point_a = (*points)[(*convex_hull)[convex_hull->size() - 2]];
            point_b = (*points)[(*convex_hull)[convex_hull->size() - 1]];
        }
        convex_hull->push_back(i);
    }
    cout << "Convex hull size = " << convex_hull->size() << endl;
}

bool is_exit(vector<vector<int>> &triangles, int t_cur) {
    int a_index = triangles[t_cur][0];
    int b_index = triangles[t_cur][1];
    int c_index = triangles[t_cur][2];
    if (a_index == -1 || b_index == -1 || c_index == -1) {
        return true;
    }
    return false;
}

void find_path_from_baricenter_to_outside(vector<Point *> *points, vector<vector<int>> &triangles, vector<vector<int>> &adjacency_list, vector<int> &path) {
    double xb = 0, yb = 0;
    for (int i = 0; i < points->size(); i++) {
        xb += (*points)[i]->x;
        yb += (*points)[i]->y;
    }
    xb /= points->size();
    yb /= points->size();

    Point *baricenter = new Point(xb, yb);
    vector<int> *tpoints = new vector<int>(3);

    Polygon *poligon = new Polygon(points, NULL);
    int t_begin;
    for (t_begin = 0; t_begin < triangles.size(); t_begin++) {
        int a_index = triangles[t_begin][0];
        int b_index = triangles[t_begin][1];
        int c_index = triangles[t_begin][2];
        (*tpoints) = {a_index, b_index, c_index};
        poligon->vert_list = tpoints;
        if (poligon->point_inside(baricenter->x, baricenter->y)) {
            break;
        }
    }

    path.push_back(t_begin);
    vector<bool> visited(triangles.size(), false);
    visited[t_begin] = true;

    int t_cur = t_begin;
    while (!is_exit(adjacency_list, t_cur)) {
        bool has_next = false;
        for (int i = 0; i < 3; i++) {
            int t_next = adjacency_list[t_cur][i];
            if (!visited[t_next]) {
                path.push_back(t_next);
                visited[t_next] = true;
                t_cur = t_next;
                has_next = true;
                break;
            }
        }
        if (!has_next) {
            path.pop_back();
            t_cur = path[path.size() - 1];
        }
    }
}
