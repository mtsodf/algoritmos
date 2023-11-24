from weighted_digraph import WeightedDigraph
from dag_generator import generate_dag
import random
import time
import sys

sys.setrecursionlimit(100000)


def test_neighbours():
    g = WeightedDigraph(2)

    g.add_edge(0, 1, 0.1)

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

    for i in range(100):
        n = 20
        g, topological_order_benchmark = generate_dag(n, False, 0.4, True)

        top_order = g.topological_order(random.randint(0, n - 1))
        check_topological_order(g, top_order)


def check_topological_order(g, top_order):
    for i in range(1, g.size):
        for j in range(i):
            assert not g.are_neighbours(top_order[i], top_order[j])


def test_kosajaru():
    g = WeightedDigraph(9)
    g.add_edge(0, 1, 0.1)
    g.add_edge(1, 2, 0.1)
    g.add_edge(2, 3, 0.1)
    g.add_edge(3, 0, 0.1)

    g.add_edge(2, 4, 0.1)
    g.add_edge(4, 5, 0.1)
    g.add_edge(5, 6, 0.1)
    g.add_edge(6, 4, 0.1)

    g.add_edge(7, 6, 0.1)
    g.add_edge(7, 8, 0.1)

    components = g.strongly_connected_components()

    set_components = [set(x) for x in components]

    assert len(components) == 4

    assert set([0, 1, 2, 3]) in set_components
    assert set([4, 5, 6]) in set_components
    assert set([7]) in set_components
    assert set([8]) in set_components


def test_time_topological_order():
    for n in [10, 100, 1000]:
        g = generate_dag(n, False, 0.5, True)[0]

        # Measure time

        start = time.time()
        top_order = g.topological_order(random.randint(0, n - 1))
        end = time.time()
        elapsed = end - start
        print(f"n={n} elapsed={elapsed}")
