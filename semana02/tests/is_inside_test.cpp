#include <iostream>
#include <fstream>
#include <vector>
#include "polygon.h"

double get_max_from_vector(vector<double> &vec)
{
    double max = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] > max)
            max = vec[i];
    }
    return max;
}

double get_min_from_vector(vector<double> &vec)
{
    double min = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < min)
            min = vec[i];
    }
    return min;
}

using namespace std;

int main()
{

    // Print current directory
    system("pwd");

    vector<double> xs, ys;
    cout << "Reading polygon from file" << endl;
    read_polygon_from_file("../../../semana02/data/caxeiro/polygon_1000_1.txt", xs, ys);
    cout << "xs size = " << xs.size() << endl;

    // Polygon p(&xs, &ys);
    Polygon *p = new Polygon(&xs, &ys);

    cout << "Getting minimum value" << endl;
    // Get x min and max from xs
    double xmin = get_min_from_vector(xs);
    double xmax = get_max_from_vector(xs);

    // Get y min and max from ys
    cout << "Getting minimum value" << endl;
    // Get x min and max from xs
    double ymin = get_min_from_vector(ys);
    double ymax = get_max_from_vector(ys);

    int n = 100;

    double delta_x = (xmax - xmin) / n;
    double delta_y = (ymax - ymin) / n;

    // Open output file
    ofstream myfile;
    myfile.open("polygon_1000_1.grid.txt");

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            double xp = xmin + i * delta_x;
            double yp = ymin + j * delta_y;
            bool inside = is_inside(p, xp, yp);
            // write to file
            myfile << xp << " " << yp << " " << inside << endl;
        }
    }
    myfile.close();
}