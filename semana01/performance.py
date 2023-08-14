import time
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
from inside_polygon import is_inside

data = {"n": [], "elapsed_time": []}

# for n in [10, 100, 1000, 10000, 100000]:
for n in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
    theta = np.linspace(0, 2*np.pi, n, endpoint=True)
    x = np.cos(theta)
    y = np.sin(theta)


    # get elapsed time
    for i in range(5): 
        start = time.time()
        is_inside(x, y, 0, 0)
        elapsed_time = time.time() - start
        data["n"].append(n)
        data["elapsed_time"].append(elapsed_time)


df = pd.DataFrame(data)
df.to_csv("data/performance.csv", index=False)

fig, ax = plt.subplots(1,1)
sns.lineplot(data=df, x="n", y="elapsed_time", errorbar=lambda x: (x.min(), x.max()), ax=ax, label="Tempo")
ax.set_xlabel("Tamanho Polígono")
ax.set_ylabel("Tempo de Execução (s)")

ax.plot([10, 1000], [1e-3, 1e-1], color="black", ls="--", label="Linear", marker="o")

ax.legend()

# Log x scale and Log y scale
ax.set_xscale("log")
ax.set_yscale("log")
plt.savefig("tex/figures/performance.png")
plt.show()