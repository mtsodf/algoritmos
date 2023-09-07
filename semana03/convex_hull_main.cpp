#include <iostream>
#include <fstream>
#include <math.h>
#include "polygon.h"

using namespace std;

void generate_random_points(int n, vector<double> &xs, vector<double> &ys)
{
    // set seed with clock value
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        // Sort random floats
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        xs.push_back(x);
        ys.push_back(y);
    }
}
vector<int> *convex_bool_to_int(vector<bool> *convex_hull_bool, vector<double> xs, vector<double> ys)
{
    vector<int> *convex_hull = new vector<int>;
    double b_x = 0, b_y = 0;
    int n = xs.size();
    for (int i = 0; i < n; i++)
    {
        if ((*convex_hull_bool)[i])
        {
            convex_hull->push_back(i);
            b_x += xs[i];
            b_y += ys[i];
        }
    }
    b_x /= convex_hull->size();
    b_y /= convex_hull->size();

    cout << "Baricenter = " << b_x << ", " << b_y << endl;
    vector<double> angles(convex_hull->size());
    for (int i = 0; i < convex_hull->size(); i++)
    {
        double PI = atan(1) * 4;
        int i_convex = (*convex_hull)[i];
        angles[i] = atan2(ys[i_convex] - b_y, xs[i_convex] - b_x) * 180 / PI;
    }

    for (int i = 0; i < convex_hull->size(); i++)
    {
        for (int j = i + 1; j < convex_hull->size(); j++)
        {
            if (angles[i] > angles[j])
            {
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

bool ccw(double xa, double ya, double xb, double yb, double xc, double yc)
{
    return (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya) > 0;
}

vector<int> *convex_hull_n3(vector<double> xs, vector<double> ys)
{
    int n = xs.size();

    vector<bool> *convex_hull_bool = new vector<bool>(n, false);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;

            double xa = xs[i], ya = ys[i];
            double xb = xs[j], yb = ys[j];
            bool all_cw = true;

            for (int k = 0; k < n; k++)
            {
                if (k != i && k != j)
                {
                    double xc = xs[k], yc = ys[k];
                    if (!ccw(xa, ya, xb, yb, xc, yc))
                    {
                        all_cw = false;
                        break;
                    }
                }
            }
            if (all_cw)
            {
                (*convex_hull_bool)[i] = true;
                (*convex_hull_bool)[j] = true;
            }
        }
    cout << "N Convex Hull = " << convex_hull_bool->size() << endl;
    return convex_bool_to_int(convex_hull_bool, xs, ys);
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

    return convex_bool_to_int(convex_hull_bool, xs, ys);
}

vector<int> *jarvis(vector<double> xs, vector<double> ys)
{
    int n = xs.size();
    vector<int> *convex_hull = new vector<int>();
    convex_hull->reserve(n);
    vector<bool> *convex_hull_bool = new vector<bool>(n, false);

    double xmin = xs[0], ymin = ys[0];

    for (int i = 0; i < n; i++)
    {
        if (xs[i] < xmin)
            xmin = xs[i];
        if (ys[i] < ymin)
            ymin = ys[i];
    }

    double x_pivot = xmin - 1;
    double y_pivot = ymin - 1;

    int cur_i = 0;
    int first_point = -1;
    int pivot_i = -1;
    int iters = 0;
    bool finished = false;
    while (!finished && iters < n + 2)
    {
        cur_i = pivot_i == 0 ? 1 : 0;
        double xb = xs[cur_i], yb = ys[cur_i];
        for (int i = 1; i < n; i++)
        {
            if (i == pivot_i)
                continue;
            double xc = xs[i], yc = ys[i];

            if (!ccw(x_pivot, y_pivot, xb, yb, xc, yc))
            {
                cur_i = i;
                xb = xs[cur_i];
                yb = ys[cur_i];
            }
        }
        (*convex_hull_bool)[cur_i] = true;
        if (cur_i == first_point)
            finished = true;
        else
        {
            pivot_i = cur_i;
            x_pivot = xs[cur_i];
            y_pivot = ys[cur_i];
            convex_hull->push_back(cur_i);
        }

        if (first_point < 0)
            first_point = cur_i;
        iters++;
    }

    if (iters == n + 2 && false)
    {
        for (int i; i < convex_hull->size(); i++)
        {
            cout << " " << (*convex_hull)[i] << endl;
        }
        cout << "Error in Jarvis" << endl;
        return NULL;
    }

    return convex_hull;
}

int main(int argc, char const *argv[])
{
    // Generate n random 2D points
    int n = 10000;
    vector<double> xs, ys;
    // generate_random_points(n, xs, ys);
    // read_polygon_from_file("../../semana02/data/spiral/spiral_1000.txt", xs, ys);
    // read_polygon_from_file("../../semana02/data/caxeiro/polygon_1000_1.txt", xs, ys);
    read_polygon_from_file("../../semana03/data/alien.txt", xs, ys);
    n = xs.size();

    // vector<int> *convex_hull = convex_hull_naive(xs, ys);
    vector<int> *convex_hull = convex_hull_n3(xs, ys);
    // vector<int> *convex_hull = jarvis(xs, ys);

    if (convex_hull == NULL)
    {
        return -1;
    }

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
