from digraph import Digraph


def test_neighbours():
    g = Digraph(2)

    g.add_edge(0, 1)

    assert g.are_neighbours(0, 1)
    assert not g.are_neighbours(1, 0)
