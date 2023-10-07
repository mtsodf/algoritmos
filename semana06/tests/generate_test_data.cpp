#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "intersection_detection.h"
#include "random_points.h"

int main() {
    int n = 10;

    for (int i = 0; i < 20; i++) {
        vector<double> start_xs, start_ys;
        generate_random_points(10, start_xs, start_ys);

        vector<double> end_xs, end_ys;
        generate_random_points(10, end_xs, end_ys);

        vector<Point*> start, end;
        for (int i = 0; i < start_xs.size(); i++) {
            start.push_back(new Point(start_xs[i], start_ys[i]));
            end.push_back(new Point(end_xs[i], end_ys[i]));
        }

        vector<pair<int, int>> intersections;
        naive_segment_intersection(start, end, intersections);

        // Print current directory
        system("pwd");

        // Write segments and intersections on json file
        fstream json_file;
        // Generate filename with i with 2 digits
        string filename = "test_data_" + to_string(i / 10) + to_string(i % 10) + ".json";
        json_file.open(filename, ios::out);
        json_file << "{\n";
        json_file << "  \"segments\": [\n";
        for (int i = 0; i < start.size(); i++) {
            json_file << "    [" << start[i]->x << ", " << start[i]->y << ", " << end[i]->x << ", " << end[i]->y << "]";
            if (i < start.size() - 1) {
                json_file << ",";
            }
            json_file << "\n";
        }
        json_file << "  ],\n";
        json_file << "  \"intersections\": [\n";
        for (int i = 0; i < intersections.size(); i++) {
            json_file << "    [" << intersections[i].first << ", " << intersections[i].second << "]";
            if (i < intersections.size() - 1) {
                json_file << ",";
            }
            json_file << "\n";
        }
        json_file << "  ]\n";
        json_file << "}\n";
    }

    return 0;
}