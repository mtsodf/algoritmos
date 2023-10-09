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
    desc.add_options()("no_intersect", po::value<int>(), "Generate no intersections segments");
    desc.add_options()("output", po::value<string>()->default_value("output.json"), "Output file");
    desc.add_options()("input", po::value<string>()->default_value(""), "Input file");
    desc.add_options()("events", po::value<string>()->default_value(""), "Output events file");
    desc.add_options()("container", po::value<string>()->default_value("list"), "Container type");
    desc.add_options()("circle", po::value<int>()->default_value(0), "Generate points in a circle");
    desc.add_options()("comma", po::value<int>()->default_value(0), "File with comma separated points");
    desc.add_options()("length", po::value<double>()->default_value(0.1), "Mean of segment lenghts");
    desc.add_options()("length_std", po::value<double>()->default_value(0.01), "Mean of segment lenghts");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    string output_filepath = vm["output"].as<string>();
    string event_filepath = vm["events"].as<string>();
    string container_type = vm["container"].as<string>();

    cout << "Output = " << output_filepath << endl;
    cout << "Event = " << event_filepath << endl;

    double length_mean = vm["length"].as<double>();
    double length_std = vm["length_std"].as<double>();

    vector<Segment *> segments;
    int n = -1;
    if (vm.count("random_points")) {
        n = vm["random_points"].as<int>();
        generate_segments(n, length_mean, length_std, segments);
    } else if (vm.count("no_intersect")) {
        n = vm["no_intersect"].as<int>();
        generate_segments_no_intersect(n, segments);
    } else if (vm.count("input")) {
        string input_file = vm["input"].as<string>();
        cout << "Input file: " << input_file << "\n";
        read_segments_from_file(input_file, segments);
    } else {
        std::cout << "No input file was given\n";
        return 1;
    }

    pair<int, int> intersection_pair;
    vector<pair<int, int>> intersections;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    if (segment_intersection(segments, intersection_pair, container_type, event_filepath))
        intersections.push_back(intersection_pair);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time: " << scientific << setprecision(8) << cpu_time_used << endl;

    // Write segments and intersections on json file
    fstream json_file;
    // Generate filename with i with 2 digits
    json_file.open(output_filepath, ios::out);
    json_file << "{\n";
    json_file << "\"n\":" << segments.size() << ",\n";
    json_file << "\"time\":" << std::scientific << std::setprecision(8) << cpu_time_used << ",\n";
    json_file << "\"container\":"
              << "\"" << container_type << "\",\n";
    json_file << "\"length\":" << length_mean << ",\n";
    json_file << "\"length_std\":" << length_std;
    if (n < 10000) {
        json_file << ",\n";
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
        json_file << "  ]";
    }
    json_file << "\n}\n";
}