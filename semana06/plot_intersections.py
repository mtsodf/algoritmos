import argparse
import numpy as np
import json
import os
import matplotlib.pyplot as plt
import csv


def find_point_intersection(xa, ya, xb, yb):
    a0 = (ya[1] - ya[0]) / (xa[1] - xa[0])
    b0 = -a0 * xa[0] + ya[0]

    a1 = (yb[1] - yb[0]) / (xb[1] - xb[0])
    b1 = -a1 * xb[0] + yb[0]

    x = (b1 - b0) / (a0 - a1)
    y = a0 * x + b0
    return x, y


def plot_segments(segments, ax):
    for i, segment in enumerate(segments):
        ax.plot(segment[0::2], segment[1::2], color="blue", marker="o")
        # Add text with the segment number
        xm = np.mean(segment[0::2])
        ym = np.mean(segment[1::2])
        a = np.array([segment[2] - segment[0], segment[3] - segment[1]])
        perp_vec = np.array([-a[1], a[0]])
        perp_vec = (perp_vec / np.linalg.norm(perp_vec)) * 0.02
        ax.text(
            xm + perp_vec[0],
            ym + perp_vec[1],
            str(i),
            horizontalalignment="center",
            verticalalignment="center",
            fontsize=14,
        )


def plot_intersections(segments, intersections, ax):
    int_x_points = []
    int_y_points = []
    for intersection in intersections:
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


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("json_file", help="File with the intersections")
    parser.add_argument("--events", "-e", help="File with all events")
    parser.add_argument("--output", "-o", default="./", help="File with all events")
    parser.add_argument("--show", "-s", action="store_true", help="Show the plot")
    # Extension selection of plots outputs
    parser.add_argument(
        "--extension", "-x", default="png", help="Extension of the output"
    )
    args = parser.parse_args()

    fig, ax = plt.subplots(1, 1, figsize=(7, 7))

    with open(args.json_file) as f:
        json_content = json.load(f)
        segments = json_content["segments"]
        intersections = json_content["intersections"]

    plot_segments(segments, ax)
    plot_intersections(segments, intersections, ax)

    coord_array = np.array(segments)
    min_y = np.min(coord_array[:, 1::2])
    max_y = np.max(coord_array[:, 1::2])

    plt.savefig(os.path.join(args.output, f"base.{args.extension}"))
    if args.show:
        plt.show()

    if args.events:
        # Read events from args.events csv file
        png_count = 0
        with open(args.events) as f:
            reader = csv.reader(f, delimiter=";")
            events = list(reader)
            for i, event in enumerate(events):
                fig, ax = plt.subplots(1, 1, figsize=(7, 7))
                plot_segments(segments, ax)
                event_type = event[0]
                if event_type == "Start":
                    seg_id = int(event[1])
                    xa = segments[seg_id][0]
                    ya = segments[seg_id][1]
                    ax.plot([xa], [ya], color="red", marker="o")

                elif event_type == "End":
                    seg_id = int(event[1])
                    xa = segments[seg_id][2]
                    ya = segments[seg_id][3]
                    ax.plot([xa], [ya], color="red", marker="o")

                ax.plot([xa, xa], [min_y, max_y], color="black", linestyle="--")
                for value in event[::-1]:
                    if value.strip().startswith("["):
                        ax.text(xa, max_y, value, fontsize=16)
                        break
                plt.savefig(
                    os.path.join(args.output, f"event_{png_count}.{args.extension}")
                )
                png_count += 1

                found = False
                for j, value in enumerate(event):
                    if "==" in value:
                        found = True
                        id0, id1 = [int(x) for x in value.split("==")]
                        ax.plot(segments[id0][0::2], segments[id0][1::2], color="red")
                        ax.plot(segments[id1][0::2], segments[id1][1::2], color="red")
                if found:
                    plt.savefig(
                        os.path.join(args.output, f"event_{png_count}.{args.extension}")
                    )
                    png_count += 1
                plt.close()


if __name__ == "__main__":
    main()
