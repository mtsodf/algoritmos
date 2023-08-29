import argparse
import sys
import os
import matplotlib.pyplot as plt
from triangulate import triangulate, read_polygon, Polygon

# increase stack size
sys.setrecursionlimit(10**5)

# Parse arguments
parser = argparse.ArgumentParser(description="Triangulate a polygon")
parser.add_argument("input", type=str, help="Input file")
parser.add_argument("--show", "-s", action="store_true", help="Show plot")
parser.add_argument("--polygononly", "-p", action="store_true", help="Show plot")
parser.add_argument("--outputdir", "-o", type=str, default="./", help="Ouput directory")
parser.add_argument(
    "--suffix", "-x", type=str, default="", help="Suffix for output file"
)

args = parser.parse_args()

# Read polygon
xs, ys = read_polygon(args.input, close_polygon=False)
polygon = Polygon(xs, ys)


fig, ax = plt.subplots(1, 1)

if not args.polygononly:
    # Triangulate
    triangs = triangulate(polygon)
    for triang in triangs:
        triang.plot(ax=ax, color="red")

polygon.plot(ax=ax, color="black")
if args.show:
    plt.show()

pngfile = os.path.splitext(args.input)[0] + args.suffix + ".png"
pngfile = os.path.join(args.outputdir, os.path.basename(pngfile))
plt.savefig(pngfile)
