import networkx as nx
import heapq


def read_from_txt(path):
    with open(path) as f:
        lines = f.readlines()
        n_vert = int(lines[0])
        n_edge = int(lines[1])

        g = WeightedGraph(n_vert)

        for line in lines[2:]:
            vert0, vert1, edge_weight = line.split()
            vert0 = int(vert0)
            vert1 = int(vert1)
            edge_weight = float(edge_weight)
            g.add_edge(vert0, vert1, edge_weight)

        return g


class WeightedGraph:
    def __init__(self, size):
        self.adj = [None] * size
        for i in range(size):
            self.adj[i] = []
        self.size = size
        self.qtd_edge = 0

    def add_edge(self, vert0, vert1, edge_weight, check=False):
        if check:
            for adj_vert, _ in self.adj[vert0]:
                if adj_vert == vert1:
                    return False

        self.adj[vert0].append((vert1, edge_weight))
        self.adj[vert1].append((vert0, edge_weight))

        self.qtd_edge += 1
        return True

    def are_neighbours(self, a, b):
        for vert, _ in self.adj[a]:
            if vert == b:
                return True
        return False

    def __str__(self):
        s = ""
        for i in range(self.size):
            s += f"{i}: {self.adj[i]}\n"
        return s

    def to_nx_graph(self):
        G = nx.DiGraph()

        G.add_nodes_from([x for x in range(self.size)])

        for i in range(self.size):
            for j in self.adj[i]:
                G.add_edge(i, j)
        return G

    def plot(self, ax, layout=nx.circular_layout, strong_components=None):
        G = self.to_nx_graph()

        pos = layout(G)

        if strong_components is None:
            nx.draw(
                G,
                pos,
                with_labels=True,
                node_color="lightblue",
                node_size=500,
                edge_color="black",
                ax=ax,
            )
        else:
            colors = ["red", "green", "blue", "yellow", "orange", "purple", "pink"]

            for i in range(len(strong_components)):
                nx.draw_networkx_nodes(
                    G.subgraph(strong_components[i]),
                    pos,
                    node_color=colors[i % len(colors)],
                    node_size=500,
                    ax=ax,
                )

            nx.draw_networkx_edges(G, pos, edge_color="black", ax=ax)
            nx.draw_networkx_labels(G, pos, ax=ax)

    def plot_top(self, ax, order):
        pos = {}
        for i in range(self.size):
            pos[order[i]] = (0, i)

        G = self.to_nx_graph()

        nx.draw_networkx_edges(
            G,
            pos,
            width=1.0,
            alpha=0.5,
            edge_color="black",
            connectionstyle="arc3, rad = 0.2",
        )

        nx.draw_networkx_nodes(G, pos, node_color="lightblue", node_size=500, ax=ax)
        nx.draw_networkx_labels(G, pos, ax=ax)

        # Remove axis
        ax.set_xticks([])
        ax.set_yticks([])

    def prim(self):
        mst = WeightedGraph(self.size)

        added = [False] * self.size
        added[0] = True

        crossing_edges = []

        add_edges(crossing_edges, 0, self.adj[0], added)

        while len(crossing_edges) > 0:
            w, vert_a, vert_b = heapq.heappop(crossing_edges)
            if not added[vert_b]:
                added[vert_b] = True
                mst.add_edge(vert_a, vert_b, w)
                add_edges(crossing_edges, vert_b, self.adj[vert_b], added)

        return mst

    def total_cost(self):
        cost = 0
        for i in range(self.size):
            for vert, w in self.adj[i]:
                cost += w
        cost /= 2
        return cost


def add_edges(crossing_edges, vert_a, edges, added):
    for vert_b, w in edges:
        if not added[vert_b]:
            heapq.heappush(crossing_edges, (w, vert_a, vert_b))
