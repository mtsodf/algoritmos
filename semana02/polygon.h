#pragma once
#include <vector>
using namespace std;

int read_polygon_from_file(const char *filename, vector<double> &x, vector<double> &y, bool comma);
int read_polygon_from_file(const char *filename, vector<double> &x, vector<double> &y);
class Polygon
{
public:
    vector<double> *xs, *ys;
    vector<int> *vert_list;
    Polygon(vector<double> *xs, vector<double> *ys);
    Polygon(vector<double> *xs, vector<double> *ys, vector<int> *vert_list);
    Polygon *semi_polygon(int i, int j, int step);
    vector<Polygon> *triangulate();
    bool point_inside(double xp, double yp);
    int get_size();
};

bool is_inside(Polygon *p, double xp, double yp);
void print_polygon(Polygon *p);