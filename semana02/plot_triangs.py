import argparse
import numpy as np
import matplotlib.pyplot as plt

argparser = argparse.ArgumentParser()
argparser.add_argument("triangs", help="triangulation file")
argparser.add_argument("--polygon", "-p", help="polygon file")

args = argparser.parse_args()

points = np.loadtxt(args.triangs)


fig, ax = plt.subplots()
triang = np.zeros((4, 2))
for i in range(0, points.shape[0], 3):
    triang[:3, :] = points[i : i + 3, :]
    triang[3, :] = points[i, :]
    ax.plot(triang[:, 0], triang[:, 1], color="black")

plt.show()
