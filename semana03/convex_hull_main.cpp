#include <iostream>
#include <fstream>
#include "polygon.h"

using namespace std;

void generate_random_points(int n, vector<double> &xs, vector<double> &ys)
{
    for (int i = 0; i < n; i++)
    {
        // Sort random floats
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        xs.push_back(x);
        ys.push_back(y);
    }
}

vector<int> *convex_hull_naive(vector<double> xs, vector<double> ys)
{
    int n = xs.size();
    vector<bool> *convex_hull_bool = new vector<bool>(n, true);

    // Generate all possible triangles
    vector<int> *three_points = new vector<int>(3);

    Polygon p(&xs, &ys);

    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            for (int k = j + 1; k < n; k++)
            {
                (*three_points)[0] = i;
                (*three_points)[1] = j;
                (*three_points)[2] = k;
                p.vert_list = three_points;
                for (int ip = 0; ip < n; ip++)
                {
                    if (ip != i && ip != j && ip != k)
                    {
                        if (p.point_inside(xs[ip], ys[ip]))
                        {
                            (*convex_hull_bool)[ip] = false;
                        }
                    }
                }
            }
    vector<int> *convex_hull = new vector<int>;
    for (int i = 0; i < n; i++)
    {
        if ((*convex_hull_bool)[i])
        {
            convex_hull->push_back(i);
        }
    }
    return convex_hull;
}

int main(int argc, char const *argv[])
{
    // Generate n random 2D points
    int n = 100;
    vector<double> xs, ys;
    generate_random_points(n, xs, ys);

    vector<int> *convex_hull = convex_hull_naive(xs, ys);

    // Write to file
    ofstream output;
    output.open("convex_hull.json");
    output << "{\n";
    output << "\"points_x\": [\n";
    for (int i = 0; i < n; i++)
    {
        output << xs[i];
        if (i < n - 1)
        {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"points_y\": [\n";
    for (int i = 0; i < n; i++)
    {
        output << ys[i];
        if (i < n - 1)
        {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"convex_hull\": [\n";
    for (int i = 0; i < convex_hull->size(); i++)
    {
        output << (*convex_hull)[i];
        if (i < convex_hull->size() - 1)
        {
            output << ",\n";
        }
    }
    output << "\n]\n";
    output << "}\n";

    output.close();

    return 0;
}
