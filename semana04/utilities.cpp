#include "utilities.h"

#include <fstream>
#include <vector>

#include "point.h"
using namespace std;
void write_points_on_json(fstream &output, vector<Point *> points) {
    int n = points.size();
    output << "\"points_x\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->x;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"points_y\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->y;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n]";
}

void write_int_matrix_on_json(fstream &output, vector<vector<int>> matrix, string name) {
    int n = matrix.size();

    output << "\"" << name << "\""
           << ": [\n";
    for (int i = 0; i < n; i++) {
        output << "[";
        for (int j = 0; j < matrix[i].size(); j++) {
            output << matrix[i][j];
            if (j < matrix[i].size() - 1) {
                output << ", ";
            }
        }
        output << "]";
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n]";
}