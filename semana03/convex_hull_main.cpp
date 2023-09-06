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

int main(int argc, char const *argv[])
{
    // Generate n random 2D points
    int n = 100;
    vector<double> xs, ys;
    generate_random_points(n, xs, ys);

    Polygon p(&xs, &ys);

    // Generate all possible triangles
    vector<int> *three_points = new vector<int>(3);

    vector<bool> *convex_hull = new vector<bool>(n, true);

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
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
                            (*convex_hull)[ip] = false;
                        }
                    }
                }
            }
        }
    }

    // Write to file
    ofstream output;
    output.open("convex_hull.txt");
    for (int i = 0; i < n; i++)
    {
        output << xs[i] << " " << ys[i] << " " << (*convex_hull)[i] << endl;
    }
    output.close();

    return 0;
}
