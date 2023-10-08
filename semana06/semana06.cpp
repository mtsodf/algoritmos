#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "data_structures.hpp"
#include "intersection_detection.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char const *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("random_points", po::value<int>(), "Generate random points");
    desc.add_options()("output", po::value<string>()->default_value("output.json"), "Output file");
    desc.add_options()("alg", po::value<string>()->default_value("std"), "Algorithm to sort points");
    desc.add_options()("circle", po::value<int>()->default_value(0), "Generate points in a circle");
    desc.add_options()("comma", po::value<int>()->default_value(0), "File with comma separated points");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    string output_filepath = vm["output"].as<string>();

    vector<Segment *> segments;
    if (vm.count("random_points")) {
        int n = vm["random_points"].as<int>();
        generate_segments(n, 0.5, 0.05, segments);

    } else {
        std::cout << "No input file was given\n";
        return 1;
    }

    pair<int, int> intersection_pair;
    vector<pair<int, int>> intersections;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    if (segment_intersection(segments, intersection_pair, "events.csv"))
        intersections.push_back(intersection_pair);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time: " << scientific << setprecision(8) << cpu_time_used << endl;

    // Write segments and intersections on json file
    fstream json_file;
    // Generate filename with i with 2 digits
    json_file.open(output_filepath, ios::out);
    json_file << "{\n";
    json_file << "\"time\":" << std::scientific << std::setprecision(8) << cpu_time_used << ",\n";
    json_file << "  \"segments\": [\n";
    for (int i = 0; i < segments.size(); i++) {
        json_file << "    [" << segments[i]->start->x << ", " << segments[i]->start->y << ", " << segments[i]->end->x << ", " << segments[i]->end->y << "]";
        if (i < segments.size() - 1) {
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