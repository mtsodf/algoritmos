import matplotlib.pyplot as plt


def check_intersect(xp, yp, xa, ya, xb, yb):
    if (ya > yp and yb > yp) or (ya <= yp and yb <= yp):
        return None

    xi = (yp - ya) * (xb - xa) / (yb - ya) + xa

    if xi > xp:
        return xi
    else:
        return None


def is_inside(xs, ys, x, y, return_intersects=False, closed_polygon=True):
    edge_count = len(xs) - 1 if closed_polygon else len(xs)
    intersects = []
    ws = 0
    for i in range(edge_count):
        next_i = i + 1 if i < edge_count - 1 else 0
        intersection = check_intersect(x, y, xs[i], ys[i], xs[next_i], ys[next_i])
        if intersection is not None:
            ws += 1
            if return_intersects:
                intersects.append(i)

    if return_intersects:
        return ws % 2 == 1, intersects

    return ws % 2 == 1


def read_polygon(filename, comma_separated=False, invert_x_y=False, close_polygon=True):
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

    if close_polygon and (xs[0] != xs[-1] or ys[0] != ys[-1]):
        xs.append(xs[0])
        ys.append(ys[0])

    if invert_x_y:
        return ys, xs
    else:
        return xs, ys


class Polygon:
    def __init__(self, xs, ys, topology=None):
        self.xs = xs
        self.ys = ys
        self.topology = topology
        if self.topology is None:
            self.topology = [i for i in range(len(xs))]

    def get_size(self):
        return len(self.topology)

    def semi_polygon(self, start, end, step=1):
        n = self.get_size()
        end = end % n
        topology = []
        while start % n != end:
            topology.append(self.topology[start % n])
            start += step

        topology.append(self.topology[start % n])

        return Polygon(self.xs, self.ys, topology)

    def plot(self, ax=None, linestyle="-", color="black"):
        if ax is None:
            fig, ax = plt.subplots(1, 1)

        xs = [self.xs[i] for i in self.topology]
        ys = [self.ys[i] for i in self.topology]
        xs = xs + [xs[0]]
        ys = ys + [ys[0]]
        ax.plot(xs, ys, marker="o", linestyle=linestyle, color=color)

    def __str__(self):
        return str(self.topology)


def triangulate(polygon, verbose=False, return_diags=False):
    if polygon.get_size() == 3:
        return [] if return_diags else [polygon]

    min_x = float("inf")
    n = polygon.get_size()
    for i, vert_index in enumerate(polygon.topology):
        if polygon.xs[vert_index] < min_x:
            min_x = polygon.xs[vert_index]
            min_x_index = vert_index
            min_x_i = i

    prev_i = (min_x_i - 1) % n
    next_i = (min_x_i + 1) % n

    prev_index = polygon.topology[prev_i]
    next_index = polygon.topology[next_i]

    triang_verts = [prev_index, min_x_index, next_index]
    triang_x = [polygon.xs[i] for i in triang_verts]
    triang_y = [polygon.ys[i] for i in triang_verts]

    max_area = -float("inf")
    max_area_i, max_index = None, None
    for i, vert_index in enumerate(polygon.topology):
        if vert_index not in triang_verts:
            xp, yp = polygon.xs[vert_index], polygon.ys[vert_index]

            if is_inside(triang_x, triang_y, xp, yp, closed_polygon=False):
                area = triang_area(triang_x, triang_y)
                if area > max_area:
                    max_area = area
                    max_area_index = vert_index
                    max_area_i = i

    if max_area_i is None:
        diag_v0 = next_i
        diag_v1 = prev_i
        diag_v0_index = next_index
        diag_v1_index = prev_index
    else:
        diag_v0 = max_area_i
        diag_v1 = min_x_i
        diag_v0_index = max_area_index
        diag_v1_index = min_x_index

    polygon1 = polygon.semi_polygon(diag_v0, diag_v1, step=+1)
    polygon2 = polygon.semi_polygon(diag_v0, diag_v1, step=-1)

    return (
        ([[diag_v0_index, diag_v1_index]] if return_diags else [])
        + triangulate(polygon1, verbose=verbose, return_diags=return_diags)
        + triangulate(polygon2, verbose=verbose, return_diags=return_diags)
    )


def triang_area(xs, ys):
    delta_x0 = xs[1] - xs[0]
    delta_y0 = ys[1] - ys[0]

    delta_x1 = xs[2] - xs[0]
    delta_y1 = ys[2] - ys[0]

    return 0.5 * abs(delta_x0 * delta_y1 - delta_y0 * delta_x1)


def coloring(pol):
    diags = triangulate(pol, return_diags=True)
    n_max = max(pol.topology)
    degrees = [0] * (n_max + 1)

    for diag in diags:
        degrees[diag[0]] += 1
        degrees[diag[1]] += 1

    colors = [-1] * pol.get_size()

    colors[0] = 1
    colors[1] = 2

    for i in range(1, pol.get_size()):
        index = pol.topology[i]
        deg = degrees[index]
        i_next = (i + 1) % pol.get_size()
        i_prev = (i - 1) % pol.get_size()
        if deg % 2 == 1:
            colors[i_next] = colors[i_prev]
        else:
            colors[i_next] = 6 - colors[i_prev] - colors[i]

    return colors


if __name__ == "__main__":
    xs, ys = read_polygon("semana02/data/asadelta.txt")
    p = Polygon(xs, ys)
    triangulate(p)
