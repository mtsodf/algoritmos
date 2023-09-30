#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "graham.h"
#include "jarvis.h"
#include "polygon.h"
#include "random_points.h"
#include "utilities.h"

namespace po = boost::program_options;

int main(int argc, char const *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("input", po::value<string>(), "Input points")("random_points", po::value<int>(), "Generate random points");
    desc.add_options()("output", po::value<string>()->default_value("convex_hull.json"), "Output file");
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

    vector<Point *> points;
    for (int i = 0; i < xs.size(); i++) {
        points.push_back(new Point(xs[i], ys[i]));
    }
    cout << "Quantidade de pontos = " << points.size() << endl;

    // Measure time of one algorithm
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    vector<int> *convex_hull = graham(&points, vm["alg"].as<string>());
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time = " << cpu_time_used << endl;

    cout << "Output file = " << output_filepath << endl;

    fstream output;
    output.open(output_filepath, ios::out);
    output << "{\n";

    output << "\"n\": " << points.size() << ",\n";
    output << "\"h\": " << convex_hull->size() << ",\n";
    output << "\"algorithm\": \""
           << "graham_" << vm["alg"].as<string>()
           << "\",\n";
    output << "\"time\": " << std::scientific << std::setprecision(8) << cpu_time_used << ",\n";

    write_points_on_json(output, points);

    output << "," << endl;
    output << "\"convex_hull\": [\n";

    for (int i = 0; i < convex_hull->size(); i++) {
        output << (*convex_hull)[i];
        if (i < convex_hull->size() - 1) {
            output << ",\n";
        }
    }
    output << "]" << endl;

    output << "}\n";
    output.close();
}