def check_intersect(xp, yp, xa, ya, xb, yb):
    if (ya > yp and yb > yp) or (ya <= yp and yb <= yp):
        return None

    xi = (yp-ya)*(xb - xa)/(yb - ya) + xa

    if xi > xp:
        return xi
    else:
        return None
    

def is_inside_pnpoly(xs, ys, x, y):
    edge_count = len(xs) - 1

    inside = False

    for i in range(edge_count):
        j = i + 1
        diff_side = (ys[i] > y) != (ys[j] > y)
        if diff_side and x < (xs[j]-xs[i]) * (y-ys[i]) / (ys[j]-ys[i]) + xs[i] :
            inside = not inside

    return inside


def is_inside(xs, ys, x, y, return_intersects=False):
    edge_count = len(xs) - 1
    intersects = []
    ws = 0
    for i in range(edge_count):
        intersection = check_intersect(x, y, xs[i], ys[i], xs[i+1], ys[i+1]) 
        if intersection is not None:
            ws += 1
            if return_intersects:
                intersects.append(i)

    if return_intersects:
        return ws % 2 == 1, intersects
    
    return ws % 2 == 1


def read_polygon(filename, comma_separated=False, invert_x_y=False):
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

    if xs[0] != xs[-1] or ys[0] != ys[-1]:
        xs.append(xs[0])
        ys.append(ys[0])

    if invert_x_y: 
        return ys, xs
    else:
        return xs, ys

