#include <boost/program_options.hpp>
#include <iostream>

#include "points_triangulation.h"
#include "polygon.h"
#include "random_points.h"
#include "utilities.h"

namespace po = boost::program_options;

int main(int argc, char const *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("input", po::value<string>(), "Input points")("random_points", po::value<int>(), "Generate random points");
    desc.add_options()("output", po::value<string>()->default_value("triangulation.json"), "Output file");
    desc.add_options()("alg", po::value<string>()->default_value("std"), "Algorithm to sort points");
    desc.add_options()("circle", po::value<int>()->default_value(0), "Generate points in a circle");
    desc.add_options()("comma", po::value<int>()->default_value(0), "File with comma separated points");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    string output_filepath = vm["output"].as<string>();

    vector<double> xs, ys;
    if (vm.count("input")) {
        string input_file = vm["input"].as<string>();
        cout << "Input file: " << input_file << "\n";
        read_polygon_from_file(input_file, xs, ys, vm["comma"].as<int>() != 0);
    } else if (vm.count("random_points")) {
        int n = vm["random_points"].as<int>();
        generate_random_points(n, xs, ys, vm["circle"].as<int>());
    } else {
        std::cout << "No input file was given\n";
        return 1;
    }

    vector<Point *> *points = new vector<Point *>;

    for (int i = 0; i < xs.size(); i++) {
        points->push_back(new Point(xs[i], ys[i]));
    }

    cout << "n = " << points->size() << endl;

    vector<vector<int>> triangles;
    vector<vector<int>> adjacency_list;
    clock_t start, end;
    double cpu_time_used;
    string alg = vm["alg"].as<string>();
    if (alg == "graham") {
        cout << "Not implemented yet.\n";
        return 1;
    } else if (alg == "trig") {
        start = clock();
        triangulate_trig(points, triangles, adjacency_list);
        end = clock();
    } else {
        cout << "Invalid algorithm\n";
        return 1;
    }
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    cout << "Time: " << cpu_time_used << endl;

    write_triangulation_json(points, &triangles, &adjacency_list, alg, cpu_time_used, output_filepath);
}