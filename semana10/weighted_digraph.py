import networkx as nx


class WeightedDigraph:
    def __init__(self, size):
        self.adj = [None] * size
        for i in range(size):
            self.adj[i] = []
        self.size = size
        self.qtd_edge = 0

    def add_edge(self, vert0, vert1, check=False):
        if check:
            for adj_vert in self.adj[vert0]:
                if adj_vert == vert1:
                    return False

        self.adj[vert0].append(vert1)
        self.qtd_edge += 1
        return True

    def bfs(self, vert_start):
        queue = []
        queue.append(vert_start)
        marcado = [False] * self.size
        marcado[vert_start] = True

        aresta_final = [-1] * self.size
        ordem_visita = [-1] * self.size

        i = 0
        while len(queue) > 0:
            v = queue.pop(0)
            ordem_visita[i] = v
            i += 1
            for w in self.adj[v]:
                if not marcado[w]:
                    aresta_final[w] = v
                    marcado[w] = True
                    queue.append(w)

        return marcado, aresta_final, ordem_visita

    def dfs(self, vert_start, marcado, visitado):
        marcado[vert_start] = True
        for v in self.adj[vert_start]:
            if not marcado[v]:
                self.dfs(v, marcado, visitado)
        visitado.append(vert_start)

    def search(self, vert_start):
        pass

    def build_path(self, aresta_final, vert_end):
        path = [vert_end]
        cur_vert = vert_end
        while aresta_final[cur_vert] != -1:
            cur_vert = aresta_final[cur_vert]
            path.append(cur_vert)

        return path[::-1]

    def are_neighbours(self, a, b):
        return b in self.adj[a]

    def reverse(self):
        g = WeightedDigraph(self.size)
        for v in range(self.size):
            for w in self.adj[v]:
                g.add_edge(w, v)
        return g

    def __str__(self):
        s = ""
        for i in range(self.size):
            s += f"{i}: {self.adj[i]}\n"
        return s

    def topological_order(self, vert_start):
        marcado = [False] * self.size
        pos_ordem = []

        self.dfs(vert_start, marcado, pos_ordem)

        for i in range(self.size):
            if not marcado[i]:
                self.dfs(i, marcado, pos_ordem)

        return pos_ordem[::-1]

    def strongly_connected_components(self):
        top_order = self.topological_order(0)
        post_order = top_order[::-1]
        components = []

        marcado = [False] * self.size
        g_reversed = self.reverse()

        while len(post_order) > 0:
            next_node = post_order.pop()
            if not marcado[next_node]:
                visitado = []
                g_reversed.dfs(next_node, marcado, visitado)
                components.append(visitado)

        return components

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
