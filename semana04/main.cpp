#include <iostream>

#include "graham.h"
#include "jarvis.h"
#include "random_points.h"

int main(int argc, char const *argv[]) {
    vector<double> xs = vector<double>();
    vector<double> ys = vector<double>();

    generate_random_points(200, xs, ys, false);

    graham(xs, ys);
}