# Add test to graph with pytest
# Path: semana07/test_graph.py
import pytest
import pandas as pd
from graph import Graph
from airports import construct_airports


def test_add_edge():
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 0)

    assert g.adj == [[1, 2, 4], [0, 2], [0, 1, 3], [2, 4], [3, 0]]


def test_bfs_dfs():
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 0)

    marcado, aresta_final, _ = g.bfs(0)

    assert marcado == [True, True, True, True, True]
    assert aresta_final == [-1, 0, 0, 2, 0] or aresta_final == [-1, 0, 0, 4, 0]

    # 0 --- 1
    # | \
    # |  \
    # |   \
    # 2     3
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
    marcado, aresta_final, _ = g.bfs(0)

    assert g.qtd_edge == 6

    g.add_edge(5, 3, check=True)
    assert g.qtd_edge == 6

    assert marcado == [True, True, True, True, True, True, False]
    assert aresta_final == [-1, 0, 0, 0, 2, 3, -1]

    path = g.build_path(aresta_final, 4)
    assert path == [0, 2, 4]

    path = g.build_path(aresta_final, 5)
    assert path == [0, 3, 5]

    marcado, ordem_visita = g.dfs(0)

    assert marcado == [True, True, True, True, True, True, False]
    assert ordem_visita == [0, 3, 5, 4, 2, 1, -1]


def test_brasilia_dfs():
    df_group = pd.read_csv('./semana07/BrFlights2_group_guiana_corrected.csv')
    df_airports, id_to_airport = construct_airports(df_group)
    g = Graph(len(df_airports))
    
    
    brasilia_id = df_airports[df_airports.city == "Brasilia"].iloc[0]["id"]
    marcado, visit_order = g.dfs(brasilia_id)

    assert visit_order[0] == brasilia_id
