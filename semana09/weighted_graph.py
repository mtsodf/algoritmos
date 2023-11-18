import networkx as nx


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
