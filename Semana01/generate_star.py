import numpy as np
import matplotlib.pyplot as plt

n = 7
theta = np.pi/(2*n)
points = np.linspace(theta, theta + 2*np.pi, n, endpoint=False)
x = np.cos(points)
y = np.sin(points)

star_order = [(x*2)%n for x in range(n)]
x = x[star_order]
y = y[star_order]


np.savetxt(f"data/star_{n}.txt", np.c_[x, y], fmt="%.3f")