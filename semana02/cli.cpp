#include <iostream>
#include <fstream>
#include "polygon.h"

int main(int argc, char const *argv[])
{

    // Read file from first argument
    vector<double> xs, ys;
    read_polygon_from_file(argv[1], xs, ys);

    Polygon *p = new Polygon(&xs, &ys);

    // Measure time
    clock_t begin = clock();
    vector<Polygon> *triangles = p->triangulate();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << argv[1] << ";" << p->vert_list->size() << ";" << elapsed_secs << endl;

    // for (int i = 0; i < triangles->size(); i++)
    // {
    // print_polygon(&(*triangles)[i]);
    // }

    return 0;
}
