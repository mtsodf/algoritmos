#include <fstream>
#include <iostream>
#include <random>

#include "intersection_detection.h"

using namespace std;

void generate_grid(int n, vector<Segment *> &segments) {
    double delta = 1000.0 / (n / 2);
    for (int i = 0; i < n / 2; i++) {
        double x0 = i * delta;
        double y0 = 0;
        double x1 = (i + 1) * delta;
        double y1 = 1000.0;
        segments.push_back(new Segment(new Point(x0, y0), new Point(x1, y1), segments.size()));
    }
    for (int i = 0; i < n / 2; i++) {
        double x0 = 0;
        double y0 = (i + 0.5) * delta;
        double x1 = 1000.0;
        double y1 = (i + 0.5) * delta;
        segments.push_back(new Segment(new Point(x0, y0), new Point(x1, y1), segments.size()));
    }
}

void read_segments_from_file(string input_file, vector<Segment *> &segments) {
    fstream file;
    file.open(input_file, ios::in);
    int id = 0;

    // Get next double
    double x0, y0, x1, y1;
    while (file >> x0 >> y0 >> x1 >> y1) {
        segments.push_back(new Segment(new Point(x0, y0), new Point(x1, y1), id++));
    }

    file.close();
}
void generate_segments_no_intersect(int n, vector<Segment *> &segments) {
    int n_sqrt = sqrt(n);
    random_device rd;   // Seed the random number generator
    mt19937 gen(rd());  // Mersenne Twister PRNG

    double delta = 100000.0 / n_sqrt;
    double epsilon = delta / 100;
    for (int i = 0; i < n_sqrt; i++) {
        for (int j = 0; j < n_sqrt; j++) {
            double x0 = i * delta + epsilon, y0 = j * delta + epsilon;
            double x1 = (i + 1) * delta - epsilon, y1 = (j + 1) * delta - epsilon;
            uniform_real_distribution<double> x_rand(x0, x1);
            uniform_real_distribution<double> y_rand(y0, y1);
            Point *p0 = new Point(x_rand(gen), y_rand(gen));
            Point *p1 = new Point(x_rand(gen), y_rand(gen));
            segments.push_back(new Segment(p0, p1, segments.size()));
        }
    }
}

void generate_big_segments_no_intersect(int n, vector<Segment *> &segments) {
    random_device rd;   // Seed the random number generator
    mt19937 gen(rd());  // Mersenne Twister PRNG
    uniform_real_distribution<double> x0_rand(0, 100);
    uniform_real_distribution<double> x1_rand(900, 1000);

    double delta = 1000.0 / n;
    for (int i = 0; i < n; i++) {
        double y0 = i * delta;
        double y1 = (i + 1) * delta;
        uniform_real_distribution<double> y_rand(y0, y1);
        Point *p0 = new Point(x0_rand(gen), y_rand(gen));
        Point *p1 = new Point(x1_rand(gen), y_rand(gen));
        segments.push_back(new Segment(p0, p1, segments.size()));
    }
}

void generate_segments(int n, double length_mean, double length_std, vector<Segment *> &segments) {
    // Create a random number generator engine
    random_device rd;                                                  // Seed the random number generator
    mt19937 gen(rd());                                                 // Mersenne Twister PRNG
    normal_distribution<double> length_dist(length_mean, length_std);  // Specify mean and standard deviation
    uniform_real_distribution<double> theta_dist(-M_PI, M_PI);
    uniform_real_distribution<double> point_dist(0, 1);

    int id = segments.size();
    for (int i = 0; i < n; i++) {
        // Generate a random normal value
        double random_length = length_dist(gen);

        if (random_length < 0) random_length = 0.0;
        double theta = theta_dist(gen);

        double x0 = point_dist(gen), y0 = point_dist(gen);
        double x1, y1;

        x1 = x0 + random_length * cos(theta);
        y1 = y0 + random_length * sin(theta);

        segments.push_back(new Segment(new Point(x0, y0), new Point(x1, y1), id++));
    }
}