import os
import numpy as np
import matplotlib.pyplot as plt


print(os.getcwd())

values = np.loadtxt("convex_hull.txt")
print(values)


xs = values[:, 0]
ys = values[:, 1]
convex_hull = values[:, 2].astype(int)

plt.scatter(xs, ys, c=convex_hull)
plt.show()
