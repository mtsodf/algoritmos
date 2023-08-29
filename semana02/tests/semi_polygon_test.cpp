#include <iostream>
#include "polygon.h"

int main(int argc, char const *argv[])
{

    vector<double> xs, ys;
    read_polygon_from_file("../../../semana02/data/asadelta.txt", xs, ys);
    Polygon *p = new Polygon(&xs, &ys);

    Polygon *p1 = p->semi_polygon(1, 3, 1);
    Polygon *p2 = p->semi_polygon(1, 3, -1);

    print_polygon(p);

    return 0;
}
