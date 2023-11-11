from digraph import Digraph
from dag_generator import generate_dag


def test_neighbours():
    g = Digraph(2)

    g.add_edge(0, 1)

    assert g.are_neighbours(0, 1)
    assert not g.are_neighbours(1, 0)


def test_generate_dag():
    g, _ = generate_dag(3)

    assert g.are_neighbours(0, 1)
    assert g.are_neighbours(0, 2)
    assert g.are_neighbours(1, 2)

    assert not g.are_neighbours(1, 0)
    assert not g.are_neighbours(2, 0)
    assert not g.are_neighbours(2, 1)

    print("Digraph generated")
    print(generate_dag(10, edge_probability=0.5, shuffle=True)[0])


def test_topological_order():
    g, topological_order_benchmark = generate_dag(5, True, 1, False)

    assert g.topological_order(0) == topological_order_benchmark
    assert g.topological_order(1) == topological_order_benchmark
    assert g.topological_order(2) == topological_order_benchmark
    assert g.topological_order(3) == topological_order_benchmark
    assert g.topological_order(4) == topological_order_benchmark

    for i in range(10):
        n = 100
        g, topological_order_benchmark = generate_dag(n, True, 0.4, True)
        for i in range(g.size):
            assert g.topological_order(i) == topological_order_benchmark
