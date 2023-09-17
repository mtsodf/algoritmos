#include <boost/program_options.hpp>
#include <iostream>

#include "graham.h"
#include "jarvis.h"
#include "polygon.h"
#include "random_points.h"

namespace po = boost::program_options;

int main(int argc, char const *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("input", po::value<string>(), "Input points")("random_points", po::value<int>(), "Generate random points");
    desc.add_options()("output", po::value<string>()->default_value("convex_hull.json"), "Output file");
    desc.add_options()("alg", po::value<string>()->default_value("jarvis"), "Algorithm to use (naive, n3, jarvis)");
    desc.add_options()("circle", po::value<int>()->default_value(0), "Generate points in a circle");
    desc.add_options()("comma", po::value<int>()->default_value(0), "File with comma separated points");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

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

    vector<Point *> points;
    for (int i = 0; i < xs.size(); i++) {
        points.push_back(new Point(xs[i], ys[i]));
    }

    graham(points);
}