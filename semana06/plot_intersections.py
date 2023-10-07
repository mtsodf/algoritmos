import argparse
import json
import matplotlib.pyplot as plt


def find_point_intersection(xa, ya, xb, yb):
    a0 = (ya[1] - ya[0]) / (xa[1] - xa[0])
    b0 = -a0 * xa[0] + ya[0]

    a1 = (yb[1] - yb[0]) / (xb[1] - xb[0])
    b1 = -a1 * xb[0] + yb[0]

    x = (b1 - b0) / (a0 - a1)
    y = a0 * x + b0
    return x, y


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("json_file", help="File with the intersections")
    args = parser.parse_args()

    fig, ax = plt.subplots(1, 1, figsize=(7, 7))

    with open(args.json_file) as f:
        json_content = json.load(f)
        segments = json_content["segments"]
        for segment in segments:
            ax.plot(segment[0::2], segment[1::2], color="blue", marker="o")

        int_x_points = []
        int_y_points = []
        for intersection in json_content["intersections"]:
            s0 = intersection[0]
            s1 = intersection[1]
            ax.plot(segments[s0][0::2], segments[s0][1::2], marker="o", color="red")
            ax.plot(segments[s1][0::2], segments[s1][1::2], marker="o", color="red")
            x, y = find_point_intersection(
                segments[s0][0::2],
                segments[s0][1::2],
                segments[s1][0::2],
                segments[s1][1::2],
            )
            int_x_points.append(x)
            int_y_points.append(y)

        ax.plot(int_x_points, int_y_points, marker="o", color="chartreuse", lw=0)

    plt.show()


if __name__ == "__main__":
    main()
