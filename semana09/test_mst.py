from weighted_graph import WeightedGraph, read_from_txt


def test_sedrick_prim():
    g = read_from_txt("./semana09/data_sedrick/tinyEWG.txt")

    mst = g.prim()
    assert mst.size == 8

    assert mst.are_neighbours(4, 5)
    assert mst.are_neighbours(5, 7)
    assert mst.are_neighbours(7, 1)
    assert mst.are_neighbours(0, 7)
    assert mst.are_neighbours(0, 2)
    assert mst.are_neighbours(2, 3)
    assert mst.are_neighbours(2, 6)


def test_simple_triangle():
    g = WeightedGraph(3)
    g.add_edge(0, 1, 1)
    g.add_edge(1, 2, 2)
    g.add_edge(2, 0, 3)

    mst = g.prim()

    assert g.are_neighbours(0, 1)
    assert g.are_neighbours(1, 2)
    assert g.are_neighbours(2, 0)
    assert g.are_neighbours(0, 2)

    assert mst.are_neighbours(0, 1)
    assert mst.are_neighbours(1, 2)
    assert not mst.are_neighbours(2, 0)

    assert mst.total_cost() == 3
