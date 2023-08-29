#include <fstream>
#include "polygon.h"

int main(int argc, char const *argv[])
{

    // Read file from first argument
    vector<double> xs, ys;
    read_polygon_from_file(argv[1], xs, ys);

    Polygon *p = new Polygon(&xs, &ys);

    vector<Polygon> *triangles = p->triangulate();

    for (int i = 0; i < triangles->size(); i++)
    {
        print_polygon(&(*triangles)[i]);
    }

    return 0;
}
