#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "polygon.h"

using namespace std;

int main()
{
    vector<double> xs, ys;
    read_polygon_from_file("../../semana01/data/alien.txt", xs, ys);
    Polygon *p = new Polygon(&xs, &ys);

    cout << "Escrevendo Alien" << endl;
    cout << "Size = " << xs.size() << endl;
    // Write polygon on stdout
    for (int i = 0; i < xs.size(); i++)
    {
        cout << xs[i] << " " << ys[i] << endl;
    }

    return 0;
}