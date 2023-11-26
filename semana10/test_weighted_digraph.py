import random
import time
import sys
import matplotlib.pyplot as plt
from weighted_digraph import WeightedDigraph, path_from_to_edges, nx
from dag_generator import generate_dag

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


def test_dag_minimum_path():
    # Test with the following weighted digraph:
    g = WeightedDigraph(4)
    g.add_edge(0, 1, 0.97)
    g.add_edge(0, 2, 0.93)
    g.add_edge(0, 3, 0.53)
    g.add_edge(1, 2, 0.14)
    g.add_edge(1, 3, 0.67)
    g.add_edge(2, 3, 0.89)

    cost, path_from = g.dag_minimum_path()

    fig, ax = plt.subplots(1, 1, figsize=(7, 7))
    g.plot(ax, edges_list=path_from_to_edges(path_from))
    plt.show()
    plt.close()

    assert_min_path(g, cost, path_from)


def test_bellman_form_random():
    for i in range(100):
        g = generate_random_graph(20, edge_propability=0.8)
        cost, path_from = g.bellman_ford()

        assert_min_path(g, cost, path_from)


def test_dag_minimum_path_random():
    for i in range(100):
        g, v_order = generate_dag(20, shuffle=False)

        cost, path_from = g.dag_minimum_path()

        assert_min_path(g, cost, path_from)


def assert_min_path(g, cost, path_from):
    gcopy = g.copy()
    for i in range(gcopy.size):
        assert not gcopy.relax_vertice(cost, path_from, i)


def generate_random_graph(n, edge_propability=1):
    g = WeightedDigraph(n)

    for i in range(n):
        for j in range(n):
            if i != j and random.uniform(0, 1) <= edge_propability:
                g.add_edge(i, j, random.uniform(0, 1))
    return g
