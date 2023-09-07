#include <stdio.h>
#include <iostream>
#include <vector>
#include "polygon.h"
using namespace std;

int inline remainder(int a, int b)
{
    return (a % b + b) % b;
}

int read_polygon_from_file(const char *filename, vector<double> &x, vector<double> &y)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }

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

Polygon *Polygon::semi_polygon(int i, int j, int step)
{
    vector<int> *new_vert_list = new vector<int>;
    int n = vert_list->size();
    i = remainder(i, n);
    j = remainder(j, n);
    int k = i;
    int size;
    if (step == 1)
    {
        size = remainder(j - i, n) + 1;
    }
    else
    {
        size = remainder(i - j, n) + 1;
    }
    new_vert_list->reserve(size);
    while (k != j)
    {
        new_vert_list->push_back((*vert_list)[k]);
        k = remainder(k + step, n);
    }
    new_vert_list->push_back((*vert_list)[j]);
    return new Polygon(xs, ys, new_vert_list);
}

bool Polygon::point_inside(double xp, double yp)
{
    vector<double> *xs = this->xs;
    vector<double> *ys = this->ys;
    vector<int> *vert_list = this->vert_list;

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

int Polygon::get_size()
{
    return vert_list->size();
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

double triang_area(double *xs, double *ys)
{
    double delta_x0 = xs[1] - xs[0];
    double delta_x1 = xs[2] - xs[0];
    double delta_y0 = ys[1] - ys[0];
    double delta_y1 = ys[2] - ys[0];
    double area = 0.5 * (delta_x0 * delta_y1 - delta_x1 * delta_y0);

    if (area < 0)
        area = -area;
    return area;
}

vector<Polygon> *Polygon::triangulate()
{
    if (this->vert_list->size() == 3)
    {
        vector<Polygon> *triangles = new vector<Polygon>;
        triangles->push_back(*this);
        return triangles;
    }

    int n = vert_list->size();
    double min_x = 1e99;
    int min_x_i = 0;
    int min_x_index = -1;
    for (int i = 0; i < n; i++)
    {
        if ((*xs)[(*vert_list)[i]] < min_x)
        {
            min_x_index = (*vert_list)[i];
            min_x = (*xs)[min_x_index];
            min_x_i = i;
        }
    }
    int prev_i = remainder(min_x_i - 1, n);
    int next_i = remainder(min_x_i + 1, n);

    int prev_index = (*vert_list)[prev_i];
    int next_index = (*vert_list)[next_i];

    double max_area = -1;
    int max_area_i = -1;
    int max_area_index = -1;

    vector<double> triang_x, triang_y;
    triang_x.reserve(3);
    triang_y.reserve(3);
    triang_x.push_back((*xs)[prev_index]);
    triang_y.push_back((*ys)[prev_index]);
    triang_x.push_back((*xs)[next_index]);
    triang_y.push_back((*ys)[next_index]);
    triang_x.push_back((*xs)[min_x_index]);
    triang_y.push_back((*ys)[min_x_index]);

    Polygon *triang = new Polygon(&triang_x, &triang_y);

    double area_triang_x[3], area_triang_y[3];
    area_triang_x[0] = (*xs)[prev_index];
    area_triang_y[0] = (*ys)[prev_index];
    area_triang_x[1] = (*xs)[next_index];
    area_triang_y[1] = (*ys)[next_index];

    for (int i = 0; i < n; i++)
    {
        int index = (*vert_list)[i];
        if (index == prev_index || index == next_index || index == min_x_index)
            continue;
        if (is_inside(triang, (*xs)[index], (*ys)[index]))
        {
            area_triang_x[2] = (*xs)[index];
            area_triang_y[2] = (*ys)[index];
            double area = triang_area(area_triang_x, area_triang_y);
            if (area > max_area)
            {
                max_area = area;
                max_area_i = i;
                max_area_index = index;
            }
        }
    }

    Polygon *p0, *p1;
    if (max_area_i == -1)
    {
        p0 = this->semi_polygon(prev_i, next_i, 1);
        p1 = this->semi_polygon(prev_i, next_i, -1);
    }
    else
    {
        p0 = this->semi_polygon(min_x_i, max_area_i, 1);
        p1 = this->semi_polygon(min_x_i, max_area_i, -1);
    }
    vector<Polygon> *triangles0 = p0->triangulate();
    vector<Polygon> *triangles1 = p1->triangulate();

    // Add elements of triangles1 to triangles0
    for (int i = 0; i < triangles1->size(); i++)
        triangles0->push_back((*triangles1)[i]);

    return triangles0;
}

void print_polygon(Polygon *p)
{
    vector<double> *xs = p->xs;
    vector<double> *ys = p->ys;
    vector<int> *vert_list = p->vert_list;

    int n = vert_list->size();
    for (int i = 0; i < n; i++)
    {
        printf("%lf %lf\n", (*xs)[(*vert_list)[i]], (*ys)[(*vert_list)[i]]);
    }
}

void print_polygon_to_file(Polygon *p, const char *filename)
{
    FILE *f = fopen(filename, "w");
    vector<double> *xs = p->xs;
    vector<double> *ys = p->ys;
    vector<int> *vert_list = p->vert_list;

    int n = vert_list->size();
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%lf %lf\n", (*xs)[(*vert_list)[i]], (*ys)[(*vert_list)[i]]);
    }
    fclose(f);
}
