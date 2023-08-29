#include <iostream>
#include "polygon.h"

int main(int argc, char const *argv[])
{

    vector<double> xs, ys;
    xs.push_back(0);
    xs.push_back(1);
    xs.push_back(1);
    xs.push_back(0);
    ys.push_back(0);
    ys.push_back(0);
    ys.push_back(1);
    ys.push_back(1);

    Polygon *p = new Polygon(&xs, &ys);
    vector<Polygon> *triangles = p->triangulate();

    cout << "Triangles: " << triangles->size() << endl;

    for (int i = 0; i < triangles->size(); i++)
    {
        cout << "Triangle " << i << endl;
        print_polygon(&(*triangles)[i]);
    }
    xs.clear();
    ys.clear();

    read_polygon_from_file("../../../semana02/data/asadelta.txt", xs, ys);

    Polygon *p2 = new Polygon(&xs, &ys);

    vector<Polygon> *triangles2 = p2->triangulate();
    for (int i = 0; i < triangles->size(); i++)
    {
        cout << "Triangle " << i << endl;
        print_polygon(&(*triangles2)[i]);
    }

    return 0;
}
