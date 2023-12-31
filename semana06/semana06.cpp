#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "data_structures.hpp"
#include "intersection_detection.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char const *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("random_points", po::value<int>(), "Generate random points");
    desc.add_options()("no_intersect", po::value<int>(), "Generate no intersections segments");
    desc.add_options()("no_intersect_big", po::value<int>(), "Generate no intersections segments");
    desc.add_options()("grid", po::value<int>(), "Generate grid segments");
    desc.add_options()("grid_vert", po::value<int>(), "Generate grid with vertical segments");
    desc.add_options()("detection", po::value<int>()->default_value(0), "Set detection or list detection");
    desc.add_options()("output", po::value<string>()->default_value("output.json"), "Output file");
    desc.add_options()("input", po::value<string>()->default_value(""), "Input file");
    desc.add_options()("events", po::value<string>()->default_value(""), "Output events file");
    desc.add_options()("container", po::value<string>()->default_value("list"), "Segment Container type");
    desc.add_options()("container_event", po::value<string>()->default_value("heap"), "Event Container type");
    desc.add_options()("length", po::value<double>()->default_value(0.1), "Mean of segment lenghts");
    desc.add_options()("length_std", po::value<double>()->default_value(0.01), "Mean of segment lenghts");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    string output_filepath = vm["output"].as<string>();
    string event_filepath = vm["events"].as<string>();
    string container_type = vm["container"].as<string>();
    string event_container_type = vm["container_event"].as<string>();
    string sort_case = "";

    cout << "Output = " << output_filepath << endl;
    cout << "Event = " << event_filepath << endl;

    double length_mean = vm["length"].as<double>();
    double length_std = vm["length_std"].as<double>();

    vector<Segment *> segments;
    int n = -1;
    if (vm.count("random_points")) {
        sort_case = "random_points";
        n = vm["random_points"].as<int>();
        generate_segments(n, length_mean, length_std, segments);
    } else if (vm.count("no_intersect")) {
        sort_case = "box";
        n = vm["no_intersect"].as<int>();
        generate_segments_no_intersect(n, segments);
    } else if (vm.count("no_intersect_big")) {
        sort_case = "big_segments";
        n = vm["no_intersect_big"].as<int>();
        generate_big_segments_no_intersect(n, segments);
    } else if (vm.count("grid")) {
        sort_case = "grid";
        n = vm["grid"].as<int>();
        generate_grid(n, segments);
    } else if (vm.count("grid_vert")) {
        sort_case = "grid_vert";
        n = vm["grid_vert"].as<int>();
        generate_vert_grid(n / 2, n / 2, segments);
    } else if (vm["input"].as<string>() != "") {
        sort_case = "input";
        string input_file = vm["input"].as<string>();
        cout << "Input file: " << input_file << "\n";
        read_segments_from_file(input_file, segments);
        n = segments.size();
    } else {
        std::cout << "No input file was given\n";
        return 1;
    }
    if (segments.size() < 10000) {
        fstream segments_file;
        segments_file.open("segments.txt", ios::out);
        for (int i = 0; i < segments.size(); i++) {
            segments_file << segments[i]->start->x << " " << segments[i]->start->y << " " << segments[i]->end->x << " " << segments[i]->end->y << "\n";
        }
        segments_file.close();
    }

    pair<int, int> intersection_pair;
    vector<pair<int, int>> intersections;
    vector<int> active_segments_size;
    active_segments_size.reserve(n);

    clock_t start, end;
    double cpu_time_used;
    bool detection = vm["detection"].as<int>() != 0;
    start = clock();
    if (container_type == "naive") {
        naive_segment_intersection(segments, intersections, detection);
    } else {
        segment_intersection(segments, intersections, &active_segments_size, container_type, event_container_type, event_filepath, detection);
    }

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
    json_file << "\"sort_case\":"
              << "\"" << sort_case << "\",\n";
    json_file << "\"container\":"
              << "\"" << container_type << "\",\n";
    json_file << "\"event_container\":"
              << "\"" << event_container_type << "\",\n";
    json_file << "\"length\":" << length_mean << ",\n";
    json_file << "\"length_std\":" << length_std << ",\n";
    if (n < 10000) {
        json_file << "  \"segments\": [\n";
        for (int i = 0; i < segments.size(); i++) {
            json_file << "    [" << segments[i]->start->x << ", " << segments[i]->start->y << ", " << segments[i]->end->x << ", " << segments[i]->end->y << "]";
            if (i < segments.size() - 1) {
                json_file << ",";
            }
            json_file << "\n";
        }
        json_file << "  ],\n";
        json_file << "  \"active_elements_size\": [\n";
        for (int i = 0; i < active_segments_size.size(); i++) {
            json_file << active_segments_size[i];
            if (i < active_segments_size.size() - 1) {
                json_file << ",";
            }
            if (i % 10 == 9) json_file << "\n";
        }
        json_file << "  ],\n";
    }
    json_file << "  \"n_intersections\": " << intersections.size() << ",\n";
    json_file << "  \"intersections\": [\n";
    if (intersections.size() < 10000) {
        for (int i = 0; i < intersections.size(); i++) {
            json_file << "    [" << intersections[i].first << ", " << intersections[i].second << "]";
            if (i < intersections.size() - 1) {
                json_file << ",";
            }
            json_file << "\n";
        }
    }
    json_file << "  ]";
    json_file << "\n}\n";
}
