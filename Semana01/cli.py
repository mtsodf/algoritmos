import argparse
import os
import matplotlib.pyplot as plt
from inside_polygon import is_inside, read_polygon, is_inside_pnpoly

args = argparse.ArgumentParser()
args.add_argument("polygon_filename", help="Polygon filename")
args.add_argument("--npoints", "-n", help="Number of grid points", type=int, default=10)
args.add_argument("--invert_axis", "-i", help="Invert axis", action="store_true")
args.add_argument("--outside", "-o", help="Plot outside points", action="store_true")
args.add_argument("--pnpoly", "-p", help="PNPOLY algorithm", action="store_true")
args.add_argument("--point", "-P", help="Point to check", nargs=2, type=float, default=None)
args.add_argument("--save", "-s", help="Save picture", action="store_true")

args = args.parse_args()

xs, ys = read_polygon(args.polygon_filename)

print(f"Qtd Vertices = {len(xs) - 1}")

fig, ax = plt.subplots(1,1)

# Invert axis directions
if args.invert_axis:
    ax.invert_yaxis()

algorithm = is_inside_pnpoly if args.pnpoly else is_inside

if args.point:
    x, y = args.point
    if algorithm(xs, ys, x, y):
        print("Point ({}, {}) is inside".format(x, y))
        c = "blue"
    else:
        print("Point ({}, {}) is outside".format(x, y))
        c = "red"
    
    ax.scatter([x], [y], color=c)

else:
    xmin, xmax = min(xs), max(xs)
    ymin, ymax = min(ys), max(ys)

    inside_x = []
    inside_y = []
    outside_x = []
    outside_y = []

    NPOINTS = args.npoints
    for i in range(NPOINTS):
        x = xmin + i*(xmax-xmin)/(NPOINTS -1)
        for j in range(NPOINTS):
            y = ymin + j*(ymax-ymin)/(NPOINTS -1)

            if algorithm(xs, ys, x, y):
                inside_x.append(x)
                inside_y.append(y)
            else:
                outside_x.append(x)
                outside_y.append(y)

    ax.scatter(inside_x, inside_y, color="blue")
    if args.outside:
        ax.scatter(outside_x, outside_y, color="red")

ax.plot(xs, ys, color="black")
ax.set_title(os.path.basename(args.polygon_filename))

if args.save:
    figure_path = os.path.splitext(args.polygon_filename)[0] + ".png"
    print(f"Saving file {figure_path}")
    plt.savefig(figure_path)
else:
    plt.show()




