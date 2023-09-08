#include <iostream>

#include "polygon.h"

bool ccw(double xa, double ya, double xb, double yb, double xc, double yc) {
    return (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya) > 0;
}

double get_min_value(vector<double> *v) {
    double min_value = (*v)[0];
    for (int i = 1; i < v->size(); i++) {
        if ((*v)[i] < min_value) min_value = (*v)[i];
    }
    return min_value;
}

double angle(double xa, double ya, double xb, double yb) {
    double dx = xb - xa;
    double dy = yb - ya;
    double angle = atan2(dy, dx);
    if (angle < 0) angle += 2 * M_PI;
    return angle * 180 / M_PI;
}

vector<int> *paper_jarvis(vector<double> xs, vector<double> ys) {
    bool verbose = true;
    int n = xs.size();

    vector<int> *convex_hull = new vector<int>();
    convex_hull->reserve(n);
    vector<bool> convex_hull_bool = vector<bool>(n, false);

    vector<int> topology;
    topology.reserve(n);

    Polygon *convex_hull_polygon = new Polygon(&xs, &ys, convex_hull);

    double xmin = get_min_value(&xs);
    double ymin = get_min_value(&ys);

    double x_pivot = xmin - 1;
    double y_pivot = ymin - 1;

    if (verbose) cout << "Pivot = " << x_pivot << ", " << y_pivot << endl;

    vector<bool> inside_hull = vector<bool>(n, false);
    vector<double> angles = vector<double>(n, INFINITY);
    int cur_i = 0;
    int first_point = -1;
    int pivot_i = -1;
    int iters = 0;
    bool finished = false;
    while (!finished && iters < n + 2) {
        double min_angle = INFINITY;
        for (int i = 0; i < n; i++) {
            if (i == pivot_i || inside_hull[i]) continue;
            double xc = xs[i], yc = ys[i];
            angles[i] = angle(x_pivot, y_pivot, xc, yc);
            if (verbose) cout << "Angle " << i << " = " << angles[i] << endl;
            if (angles[i] < min_angle) {
                cur_i = i;
                min_angle = angles[i];
            }
        }

        convex_hull_bool[cur_i] = true;

        if (cur_i == first_point)
            finished = true;
        else {
            if (verbose) cout << "Selected " << cur_i << endl;
            pivot_i = cur_i;
            x_pivot = xs[cur_i];
            y_pivot = ys[cur_i];
            convex_hull->push_back(cur_i);
            if (iters > 0) inside_hull[cur_i] = true;

            if (iters >= 2) {
                double max_angle = angle(x_pivot, y_pivot, xs[first_point], ys[first_point]);
                for (int i = 0; i < n; i++) {
                    if (i == pivot_i || inside_hull[i] || i == first_point) continue;
                    if (angles[i] > max_angle) {
                        inside_hull[i] = true;
                        if (verbose) cout << "Point " << i << " is inside convex hull" << endl;
                    }
                }
            }
        }
        if (iters == 0) first_point = cur_i;

        iters++;
    }

    if (iters == n + 2 && false) {
        for (int i; i < convex_hull->size(); i++) {
            cout << " " << (*convex_hull)[i] << endl;
        }
        cout << "Error in Jarvis" << endl;
        return NULL;
    }

    return convex_hull;
}

vector<int> *jarvis(vector<double> xs, vector<double> ys) {
    int n = xs.size();
    vector<int> *convex_hull = new vector<int>();
    convex_hull->reserve(n);
    vector<bool> *convex_hull_bool = new vector<bool>(n, false);

    double xmin = xs[0], ymin = ys[0];

    for (int i = 0; i < n; i++) {
        if (xs[i] < xmin) xmin = xs[i];
        if (ys[i] < ymin) ymin = ys[i];
    }

    double x_pivot = xmin - 1;
    double y_pivot = ymin - 1;

    int cur_i = 0;
    int first_point = -1;
    int pivot_i = -1;
    int iters = 0;
    bool finished = false;
    while (!finished && iters < n + 2) {
        cur_i = pivot_i == 0 ? 1 : 0;
        double xb = xs[cur_i], yb = ys[cur_i];
        for (int i = 1; i < n; i++) {
            if (i == pivot_i) continue;
            double xc = xs[i], yc = ys[i];

            if (!ccw(x_pivot, y_pivot, xb, yb, xc, yc)) {
                cur_i = i;
                xb = xs[cur_i];
                yb = ys[cur_i];
            }
        }
        (*convex_hull_bool)[cur_i] = true;
        if (cur_i == first_point)
            finished = true;
        else {
            pivot_i = cur_i;
            x_pivot = xs[cur_i];
            y_pivot = ys[cur_i];
            convex_hull->push_back(cur_i);
        }

        if (first_point < 0) first_point = cur_i;
        iters++;
    }

    if (iters == n + 2 && false) {
        for (int i; i < convex_hull->size(); i++) {
            cout << " " << (*convex_hull)[i] << endl;
        }
        cout << "Error in Jarvis" << endl;
        return NULL;
    }

    return convex_hull;
}
