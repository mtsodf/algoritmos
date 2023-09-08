#pragma once

#include <vector>
using namespace std;

bool ccw(double xa, double ya, double xb, double yb, double xc, double yc);
vector<int> *jarvis(vector<double> xs, vector<double> ys);
vector<int> *paper_jarvis(vector<double> xs, vector<double> ys);