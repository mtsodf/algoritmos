
void write_points_on_json(fstream &output, vector<Point *> points) {
    int n = points.size();
    output << "\"points_x\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->x;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n],\n";
    output << "\"points_y\": [\n";
    for (int i = 0; i < n; i++) {
        output << points[i]->y;
        if (i < n - 1) {
            output << ",\n";
        }
    }
    output << "\n]";
}