import matplotlib.pyplot as plt
from weighted_graph import WeightedGraph, read_from_txt


def test_sedrick_prim():
    g = read_from_txt("./semana09/data_sedrick/tinyEWG.txt")

    mst = g.prim_lazy()
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
    g = read_from_txt("./semana09/data_sedrick/mediumEWG.txt")
    fig, axs = plt.subplots(1, 1, figsize=(7, 7))

    g.plot_with_mst(axs, plot_vertices=False)
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
