import time
import random
import matplotlib.pyplot as plt
from weighted_graph import WeightedGraph, generate_random_tree, read_from_txt


def generate_random_graph(n_vert, n_add_edge):
    g = generate_random_tree(n_vert)
    mst_benchmark = g.copy()

    total_cost = mst_benchmark.total_cost()
    for i in range(n_add_edge):
        v, w = random.randint(0, n_vert - 1), random.randint(0, n_vert - 1)
        if v != w and not g.are_neighbours(v, w):
            weight = total_cost + random.uniform(0, 1)
            g.add_edge(v, w, weight)

    return g, mst_benchmark


def test_with_random_graph():
    for n_vert in [20, 40, 80]:
        n_add_edge = n_vert * 2
        for i in range(10):
            g, mst_benchmark = generate_random_graph(n_vert, n_add_edge)

            for alg in [g.prim_lazy, g.kruskal]:
                mst = alg()

                assert mst.size == n_vert

                for i in range(n_vert):
                    for j in range(i + 1, n_vert):
                        if mst_benchmark.are_neighbours(i, j):
                            assert mst.are_neighbours(i, j)
                            assert mst.are_neighbours(j, i)
                        else:
                            assert not mst.are_neighbours(i, j)
                            assert not mst.are_neighbours(j, i)


def test_sedrick_prim():
    g = read_from_txt("./semana09/data_sedrick/tinyEWG.txt")

    for alg in [g.prim_lazy, g.kruskal]:
        mst = alg()
        assert mst.size == 8

        edges_benchmark = [(4, 5), (5, 7), (1, 7), (0, 7), (0, 2), (2, 3), (2, 6)]

        for i in range(g.size):
            for j in range(i + 1, g.size):
                if (i, j) in edges_benchmark:
                    assert mst.are_neighbours(i, j)
                    assert mst.are_neighbours(j, i)
                else:
                    assert not mst.are_neighbours(i, j)
                    assert not mst.are_neighbours(j, i)


def test_bigger():
    # g = read_from_txt("./semana09/data_sedrick/mediumEWG.txt")
    g = read_from_txt("./semana09/data_sedrick/1000EWG.txt")

    # Measure kruskal time
    start = time.time()
    mst_kruskal = g.kruskal()
    kruskal_time = time.time() - start
    start = time.time()
    mst_prim = g.prim_lazy()
    prim_time = time.time() - start

    print("Kruskal time:", kruskal_time)
    print("Prim time:   ", prim_time)

    fig, axs = plt.subplots(1, 2, figsize=(16, 7))

    pos = g.plot(axs[0], edge_color="gray", plot_vertices=False)
    g.plot(axs[1], pos=pos, edge_color="gray", plot_vertices=False)

    mst_kruskal.plot(axs[0], pos=pos, edge_color="red", plot_vertices=False)
    mst_prim.plot(axs[1], pos=pos, edge_color="red", plot_vertices=False)

    axs[0].set_title(f"Kruskal - Elapsed Time {kruskal_time:f} s")
    axs[1].set_title(f"Prim - Elapsed Time {prim_time:f} s")

    plt.show()
    plt.close()


def test_simple_triangle():
    g = WeightedGraph(3)
    g.add_edge(0, 1, 1)
    g.add_edge(1, 2, 2)
    g.add_edge(2, 0, 3)

    mst = g.prim_lazy()

    assert g.are_neighbours(0, 1)
    assert g.are_neighbours(1, 2)
    assert g.are_neighbours(2, 0)
    assert g.are_neighbours(0, 2)

    assert mst.are_neighbours(0, 1)
    assert mst.are_neighbours(1, 2)
    assert not mst.are_neighbours(2, 0)

    assert mst.total_cost() == 3
