#include <stdio.h>
#include <vector>
#include "polygon.h"
using namespace std;

int read_polygon_from_file(const char *filename, vector<double> &x, vector<double> &y)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return -1;

    // Read while not end of file
    int n = 0;
    while (!feof(f))
    {
        double x0, y0;
        fscanf(f, "%lf %lf", &x0, &y0);
        x.push_back(x0);
        y.push_back(y0);
        n++;
    }

    fclose(f);
    return n;
}

Polygon::Polygon(vector<double> *xs, vector<double> *ys)
{
    this->xs = xs;
    this->ys = ys;

    int n = xs->size();

    // Create a list of vertices
    vert_list = new vector<int>;
    for (int i = 0; i < n; i++)
    {
        vert_list->push_back(i);
    }
}

Polygon::Polygon(vector<double> *xs, vector<double> *ys, vector<int> *vert_list)
{
    this->xs = xs;
    this->ys = ys;
    this->vert_list = vert_list;
}

bool is_inside(Polygon *p, double xp, double yp)
{
    vector<double> *xs = p->xs;
    vector<double> *ys = p->ys;
    vector<int> *vert_list = p->vert_list;

    int n = vert_list->size();
    int j = n - 1;
    int cont = 0;
    for (int i = 0; i < n; j = i++)
    {
        double xi = (*xs)[(*vert_list)[i]];
        double yi = (*ys)[(*vert_list)[i]];
        double xj = (*xs)[(*vert_list)[j]];
        double yj = (*ys)[(*vert_list)[j]];

        if (((yi > yp) != (yj > yp)) && (xp < (xj - xi) * (yp - yi) / (yj - yi) + xi))
            cont++;
    }
    return cont % 2 == 1;
}
