#include <iostream>
#include <vector>

using namespace std;

void generate_random_points(int n, vector<double> &xs, vector<double> &ys, bool circle = false) {
    // set seed with clock value
    int seed = clock();
    // seed = 1694207106;
    // seed = 1694207162;
    cout << "Current SEED = " << seed << endl;
    srand(seed);

    for (int i = 0; i < n; i++) {
        // Sort random floats
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (circle) {
            double theta = 2 * M_PI * x;
            double r = y;
            x = r * cos(theta);
            y = r * sin(theta);
        }
        xs.push_back(x);
        ys.push_back(y);
    }
}