import os
import json
import numpy as np
import matplotlib.pyplot as plt


with open("convex_hull.json", "r") as f:
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

plt.scatter(xs, ys, c=colors)
plt.plot(convex_x, convex_y)
# add point index text
for i in convex_hull[::-1]:
    plt.text(xs[i], ys[i], str(i))
plt.show()
