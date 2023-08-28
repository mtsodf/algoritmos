import argparse
from triangulate import read_polygon, Polygon
import matplotlib.pyplot as plt


if __name__ == "__main__":
    # add the arguments to the parser
    parser = argparse.ArgumentParser()
    # add argument to receive a polygon file
    parser.add_argument("polygon", help="polygon file")
    # add argument to read the classification of the points
    parser.add_argument("--classification", "-c", help="classification file")
    # add marker size argument
    parser.add_argument(
        "--marker-size", "-m", type=float, default=1.0, help="marker size"
    )

    # parse the arguments
    args = parser.parse_args()

    # read the polygon file
    xs, ys = read_polygon(args.polygon, close_polygon=False)
    polygon = Polygon(xs, ys)
    fig, ax = plt.subplots()
    polygon.plot(ax=ax, marker=None)

    # read the classification file
    if args.classification is not None:
        with open(args.classification) as f:
            inside = []
            outside = []
            for line in f:
                x, y, c = line.split()
                x = float(x)
                y = float(y)
                c = int(c)
                if c == 1:
                    inside.append((x, y))
                else:
                    outside.append((x, y))
            # Plot inside
            xs = [x for x, y in inside]
            ys = [y for x, y in inside]
            ax.plot(xs, ys, "o", color="blue", markersize=args.marker_size)
            xs = [x for x, y in outside]
            ys = [y for x, y in outside]
            ax.plot(xs, ys, "o", color="red", markersize=args.marker_size)

    plt.show()
