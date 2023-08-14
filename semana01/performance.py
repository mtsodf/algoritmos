import time
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
from inside_polygon import is_inside

data = {"n": [], "elapsed_time": []}

for n in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
# for n in [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]:
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

sns.lineplot(data=df, x="n", y="elapsed_time", errorbar=lambda x: (x.min(), x.max()))
plt.xlabel("Tamanho Polígono")
plt.ylabel("Tempo de Execução (s)")

# Log x scale and Log y scale
plt.xscale("log")
plt.yscale("log")
plt.savefig("tex/figures/performance.png")
plt.show()