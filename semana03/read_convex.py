import os
import json
import numpy as np
import matplotlib.pyplot as plt


with open("convex_hull.json", "r") as f:
    json_values = json.load(f)


xs = json_values["points_x"]
ys = json_values["points_y"]
convex_hull = json_values["convex_hull"]

colors = np.zeros(len(xs))
colors[convex_hull] = 1

plt.scatter(xs, ys, c=colors)
plt.show()
