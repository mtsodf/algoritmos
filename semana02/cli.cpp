#include <iostream>
#include <fstream>
#include <chrono>
#include "polygon.h"

int main(int argc, char const *argv[])
{

    // Read file from first argument
    vector<double> xs, ys;
    read_polygon_from_file(argv[1], xs, ys);

    Polygon *p = new Polygon(&xs, &ys);

    // Measure time
    //clock_t begin = clock();
    auto start = std::chrono::high_resolution_clock::now();
    vector<Polygon> *triangles = p->triangulate();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double elapsed_secs = duration.count();
    
    //clock_t end = clock();
    //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    //cout << argv[1] << ";" << p->vert_list->size() << ";" << std:setprecision(15) << elapsed_secs << endl;
    printf("%s;%d;%e\n", argv[1], p->vert_list->size(), elapsed_secs );

    // for (int i = 0; i < triangles->size(); i++)
    // {
    // print_polygon(&(*triangles)[i]);
    // }

    return 0;
}
