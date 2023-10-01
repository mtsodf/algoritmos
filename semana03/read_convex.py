import argparse
import os
import json
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument("files", nargs="+", default="convex_hull.json")
parser.add_argument("--point_labels", "-pl", action="store_true")
parser.add_argument("--marker_size", "-ms", type=int, default=None)
parser.add_argument("--equal", "-e", action="store_true")
parser.add_argument("--invert_x", "-ix", action="store_true")
parser.add_argument("--invert_y", "-iy", action="store_true")
parser.add_argument("--show", "-s", action="store_true")
parser.add_argument("--adj", "-ad", action="store_true")

args = parser.parse_args()

for points_file in args.files:
    with open(points_file, "r") as f:
        json_values = json.load(f)

    xs = np.array(json_values["points_x"])
    ys = np.array(json_values["points_y"])

    fig, ax = plt.subplots(1, 1)
    ax.scatter(xs, ys, s=args.marker_size)

    if args.invert_x:
        ax.invert_xaxis()

    if args.invert_y:
        ax.invert_yaxis()

    if args.point_labels:
        for i in range(len(xs)):
            ax.text(xs[i], ys[i], str(i))

    # set equal scale
    if args.equal:
        ax.set_aspect("equal", "box")

    output = os.path.splitext(points_file)[0] + "_pointsonly.png"
    fig.savefig(output)

    if "convex_hull" in json_values:
        convex_hull = json_values["convex_hull"]
        convex_hull.append(convex_hull[0])

        convex_x = xs[convex_hull]
        convex_y = ys[convex_hull]

        ax.scatter(
            convex_x,
            convex_y,
            c="r",
            s=None if args.marker_size is None else args.marker_size * 2,
        )
        ax.plot(convex_x, convex_y, color="black")

        output = os.path.splitext(points_file)[0] + ".png"
        fig.savefig(output)
    if args.adj:
        triangles = json_values["triangles"]
        for trig in triangles:
            for i in range(3):
                ax.plot(
                    [xs[trig[i]], xs[trig[(i + 1) % 3]]],
                    [ys[trig[i]], ys[trig[(i + 1) % 3]]],
                    color="black",
                )
        for i, adj in enumerate(json_values["adjacency_list"]):
            for j in adj:
                if j >= 0:
                    xb_0 = np.mean(xs[triangles[i]])
                    yb_0 = np.mean(ys[triangles[i]])
                    xb_1 = np.mean(xs[triangles[j]])
                    yb_1 = np.mean(ys[triangles[j]])
                    ax.plot([xb_0, xb_1], [yb_0, yb_1], color="blue", marker="o")
                    xb_0 = np.mean(xs[triangles[i]])
                    yb_0 = np.mean(ys[triangles[i]])

    if args.show:
        plt.show()

    plt.close()
