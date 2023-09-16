#include <math.h>

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "jarvis.h"
#include "polygon.h"
#include "random_points.h"

using namespace std;

vector<int> *convex_bool_to_int(vector<bool> *convex_hull_bool,
                                vector<double> xs, vector<double> ys) {
    vector<int> *convex_hull = new vector<int>;
    double b_x = 0, b_y = 0;
    int n = xs.size();
    for (int i = 0; i < n; i++) {
        if ((*convex_hull_bool)[i]) {
            convex_hull->push_back(i);
            b_x += xs[i];
            b_y += ys[i];
        }
    }
    b_x /= convex_hull->size();
    b_y /= convex_hull->size();

    vector<double> angles(convex_hull->size());
    for (int i = 0; i < convex_hull->size(); i++) {
        int i_convex = (*convex_hull)[i];
        angles[i] = atan2(ys[i_convex] - b_y, xs[i_convex] - b_x) * 180 / M_PI;
    }

    for (int i = 0; i < convex_hull->size(); i++) {
        for (int j = i + 1; j < convex_hull->size(); j++) {
            if (angles[i] > angles[j]) {
                int temp = (*convex_hull)[i];
                (*convex_hull)[i] = (*convex_hull)[j];
                (*convex_hull)[j] = temp;
                double temp_double = angles[i];
                angles[i] = angles[j];
                angles[j] = temp_double;
            }
        }
    }

    return convex_hull;
}

vector<int> *convex_hull_n3(vector<double> xs, vector<double> ys) {
    int n = xs.size();
    vector<bool> *convex_hull_bool = new vector<bool>(n, false);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            double xa = xs[i], ya = ys[i];
            double xb = xs[j], yb = ys[j];
            bool all_cw = true;

            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    double xc = xs[k], yc = ys[k];
                    if (!ccw(xa, ya, xb, yb, xc, yc)) {
                        all_cw = false;
                        break;
                    }
                }
            }
            if (all_cw) {
                (*convex_hull_bool)[i] = true;
                (*convex_hull_bool)[j] = true;
            }
        }
    cout << "N Convex Hull = " << convex_hull_bool->size() << endl;
    return convex_bool_to_int(convex_hull_bool, xs, ys);
}

vector<int> *convex_hull_naive(vector<double> xs, vector<double> ys) {
    int n = xs.size();
    vector<bool> *convex_hull_bool = new vector<bool>(n, true);

    // Generate all possible triangles
    vector<int> *three_points = new vector<int>(3);

    Polygon p(&xs, &ys);

    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            for (int k = j + 1; k < n; k++) {
                (*three_points)[0] = i;
                (*three_points)[1] = j;
                (*three_points)[2] = k;
                p.vert_list = three_points;
                for (int ip = 0; ip < n; ip++) {
                    if (ip != i && ip != j && ip != k) {
                        if (p.point_inside(xs[ip], ys[ip])) {
                            (*convex_hull_bool)[ip] = false;
                        }
                    }
                }
            }

    return convex_bool_to_int(convex_hull_bool, xs, ys);
}

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

    string output_filepath = vm["output"].as<string>();
    string algname = vm["alg"].as<string>();

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

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
    int n = xs.size();
    cout << "Problem size = " << n << endl;

    // Measure time of one algorithm
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    vector<int> *convex_hull;
    if (algname == "naive")
        convex_hull = convex_hull_naive(xs, ys);
    else if (algname == "n3")
        convex_hull = convex_hull_n3(xs, ys);
    else if (algname == "jarvis")
        convex_hull = paper_jarvis(xs, ys);
    else {
        cout << "Algorithm not found" << endl;
        return -1;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time = " << cpu_time_used << endl;

    if (convex_hull == NULL) return -1;

    // Write to file
    ofstream output;
    output.open(output_filepath);
    output << "{\n";
    output << "\"n\": " << n << ",\n";
    output << "\"h\": " << convex_hull->size() << ",\n";
    output << "\"algorithm\": \"" << algname << "\",\n";
    output << "\"time\": " << std::scientific << std::setprecision(8) << cpu_time_used << ",\n";
    output << "\"points_x\": [\n";
    for (int i = 0; i < n; i++) {
        output << xs[i];
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"points_y\": [\n";
    for (int i = 0; i < n; i++) {
        output << ys[i];
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"convex_hull\": [\n";
    for (int i = 0; i < convex_hull->size(); i++) {
        output << (*convex_hull)[i];
        if (i < convex_hull->size() - 1) {
            output << ",\n";
        }
    }
    output << "\n]\n";
    output << "}\n";

    output.close();

    return 0;
}
