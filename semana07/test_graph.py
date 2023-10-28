# Add test to graph with pytest
# Path: semana07/test_graph.py
import pytest
from graph import Graph


def test_add_edge():
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 0)

    assert g.adj == [[1, 2, 4], [0, 2], [0, 1, 3], [2, 4], [3, 0]]


def test_bfs():
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 0)

    marcado, aresta_final = g.bfs(0)

    assert marcado == [True, True, True, True, True]
    assert aresta_final == [-1, 0, 0, 2, 0] or aresta_final == [-1, 0, 0, 4, 0]

    # 0 --- 1
    # | \   |
    # |  \  |
    # |   \ |
    # 2 --- 3
    # |     |
    # |     |
    # 4 --- 5
    g = Graph(7)

    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(0, 3)
    g.add_edge(2, 4)
    g.add_edge(4, 5)
    g.add_edge(3, 5)
    marcado, aresta_final = g.bfs(0)

    assert marcado == [True, True, True, True, True, True, False]
    assert aresta_final == [-1, 0, 0, 0, 2, 3, -1]

    path = g.build_path(aresta_final, 4)
    assert path == [0, 2, 4]

    path = g.build_path(aresta_final, 5)
    assert path == [0, 3, 5]
