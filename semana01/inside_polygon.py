def check_intersect(xa, ya, xb, yb):
    if (ya > 0) == (yb > 0):
        return 0

    xi = -ya*(xb - xa)/(yb - ya) + xa

    if xi > 0:
        return 1 if yb > ya else -1
    return 0
    

def is_inside_pnpoly(xs, ys, x, y):
    edge_count = len(xs) - 1

    inside = False

    for i in range(edge_count):
        j = i + 1
        diff_side = (ys[i] > y) != (ys[j] > y)
        if diff_side and x < (xs[j]-xs[i]) * (y-ys[i]) / (ys[j]-ys[i]) + xs[i] :
            inside = not inside

    return inside


def is_inside(xs, ys, x, y):
    edge_count = len(xs) - 1

    ws = 0
    for i in range(edge_count):
        ws += check_intersect(xs[i]-x, ys[i]-y, xs[i+1]-x, ys[i+1]-y)

    return ws % 2 == 1


def read_polygon(filename, comma_separated=False):
    xs = []
    ys = []    
    with open(filename) as f:
        for line in f:
            if "," in line:
                x, y = [float(value) for value in line.split(",")]
            else:
                x, y = [float(value) for value in line.split()]
            xs.append(x)
            ys.append(y)
    if xs[0] != xs[-1] and ys[0] != ys[-1]:
        xs.append(xs[0])
        ys.append(ys[0])
    return xs, ys

