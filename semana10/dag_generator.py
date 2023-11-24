from weighted_digraph import WeightedDigraph
import random
import numpy as np


def generate_dag(n, one_topological_order=True, edge_probability=1.0, shuffle=False):
    g = WeightedDigraph(n)

    vertices_permutation = list(range(n))

    if shuffle:
        np.random.shuffle(vertices_permutation)

    for i in range(n - 1):
        for j in range(i + 1, n):
            if (j == i + 1 and one_topological_order) or (random.random() < edge_probability):
                g.add_edge(vertices_permutation[i], vertices_permutation[j])

    return g, vertices_permutation
