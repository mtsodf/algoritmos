#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void generate_random_points(int n, vector<double> &xs, vector<double> &ys, bool circle = false) {
    xs.reserve(n);
    ys.reserve(n);
    // set seed with clock value
    int seed = clock();
    // seed = 1694207106;
    // seed = 1694207162;
    cout << "Current SEED = " << seed << endl;
    srand(seed);

    while (xs.size() < n) {
        // Sort random floats
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (circle) {
            if ((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5) > 0.5 * 0.5) continue;
        }
        xs.push_back(x);
        ys.push_back(y);
    }
}

void generate_regular_polygon(int n, vector<double> &xs, vector<double> &ys) {
    xs.reserve(n);
    ys.reserve(n);

    for (int i = 0; i < n; i++) {
        double x = cos(2 * M_PI * i / n);
        double y = sin(2 * M_PI * i / n);
        xs.push_back(x);
        ys.push_back(y);
    }
}
