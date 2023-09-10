import argparse
import os
import json
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument("files", nargs="+", default="convex_hull.json")
parser.add_argument("--point_labels", "-pl", action="store_true")
parser.add_argument("--equal", "-e", action="store_true")
parser.add_argument("--invert_x", "-ix", action="store_true")
parser.add_argument("--invert_y", "-iy", action="store_true")
parser.add_argument("--output", "-o")
parser.add_argument("--show", "-s", action="store_true")

args = parser.parse_args()

for points_file in args.files:
    with open(points_file, "r") as f:
        json_values = json.load(f)

    xs = np.array(json_values["points_x"])
    ys = np.array(json_values["points_y"])

    convex_hull = json_values["convex_hull"]
    convex_hull.append(convex_hull[0])

    print(convex_hull)

    convex_x = xs[convex_hull]
    convex_y = ys[convex_hull]

    colors = np.zeros(len(xs))
    colors[convex_hull] = 1

    fig, ax = plt.subplots(1, 1)
    ax.scatter(xs, ys)
    ax.scatter(convex_x, convex_y, c="r")
    ax.plot(convex_x, convex_y)

    if args.point_labels:
        # add point index text
        for i in convex_hull[::-1]:
            ax.text(xs[i], ys[i], str(i))
        for i in range(len(xs)):
            ax.text(xs[i], ys[i], str(i))

    # set equal scale
    if args.equal:
        ax.set_aspect("equal", "box")

    if args.invert_x:
        ax.invert_xaxis()

    if args.invert_y:
        ax.invert_yaxis()

    if args.output is None:
        output = os.path.splitext(points_file)[0] + ".png"
    else:
        output = args.output

    fig.savefig(output)

    if args.show:
        plt.show()

    plt.close()
