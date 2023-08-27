import argparse
import sys
import matplotlib.pyplot as plt
from triangulate import triangulate, read_polygon, Polygon

# increase stack size
sys.setrecursionlimit(10**5)

# Parse arguments
parser = argparse.ArgumentParser(description="Triangulate a polygon")
parser.add_argument(
    "--input", type=str, help="Input file", default="./semana02/data/asadelta.txt"
)

args = parser.parse_args()

# Read polygon
xs, ys = read_polygon(args.input, close_polygon=False)
polygon = Polygon(xs, ys)

# Triangulate
triangs = triangulate(polygon)

fig, ax = plt.subplots(1, 1)

triangs = triangulate(polygon)
for triang in triangs:
    triang.plot(ax=ax, color="red")

polygon.plot(ax=ax, linestyle="--")
plt.show()
