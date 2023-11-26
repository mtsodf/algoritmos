import networkx as nx


class WeightedDigraph:
    def __init__(self, size):
        self.adj = [None] * size
        for i in range(size):
            self.adj[i] = []
        self.size = size
        self.qtd_edge = 0

    def add_edge(self, vert0, vert1, weight, check=False):
        if check:
            for adj_vert in self.adj[vert0]:
                if adj_vert == vert1:
                    return False

        self.adj[vert0].append((vert1, weight))
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
            for w, _ in self.adj[v]:
                if not marcado[w]:
                    aresta_final[w] = v
                    marcado[w] = True
                    queue.append(w)

        return marcado, aresta_final, ordem_visita

    def dfs(self, vert_start, marcado, visitado):
        marcado[vert_start] = True
        for v, _ in self.adj[vert_start]:
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
        for v, w in self.adj[a]:
            if v == b:
                return True
        return False

    def reverse(self):
        g = WeightedDigraph(self.size)
        for v in range(self.size):
            for b, w in self.adj[v]:
                g.add_edge(b, v, w)
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
            for j, w in self.adj[i]:
                G.add_edge(i, j, weight=w)
        return G

    def plot(self, ax, layout=nx.circular_layout, strong_components=None, edge_weights=True, edges_list=None):
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
                    G.subgraph(strong_components[i]), pos, node_color=colors[i % len(colors)], node_size=500, ax=ax
                )

            nx.draw_networkx_edges(G, pos, edge_color="black", ax=ax)
            nx.draw_networkx_labels(G, pos, ax=ax)

        if edge_weights:
            labels = {}
            for edge in G.edges:
                labels[edge] = G.edges[edge]["weight"]
            nx.draw_networkx_edge_labels(G, pos, ax=ax, edge_labels=labels, label_pos=0.3)

        if edges_list is not None:
            gsub = G.edge_subgraph(edges_list)
            for edge in gsub.edges:
                print(edge)
            nx.draw_networkx_edges(gsub, pos, width=3.0, alpha=0.5, edge_color="red", ax=ax)

    def plot_top(self, ax, order=None, edge_weights=True):
        if order is None:
            order = self.topological_order(0)

        pos = {}
        for i in range(self.size):
            pos[order[i]] = (i, 0)

        G = self.to_nx_graph()

        # Draw edges with weights
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

        if edge_weights:
            labels = {}
            for edge in G.edges:
                labels[edge] = round(G.edges[edge]["weight"], 2)
            nx.draw_networkx_edge_labels(G, pos, ax=ax, edge_labels=labels)

        # Remove axis
        ax.set_xticks([])
        ax.set_yticks([])

    def relax_edge(self, path_cost, path_from, a, b, weight):
        if path_cost[a] + weight < path_cost[b]:
            path_from[b] = a
            path_cost[b] = path_cost[a] + weight
            return True
        return False

    def relax_vertice(self, path_cost, path_from, a):
        any_relaxed = False
        for b, weight in self.adj[a]:
            any_relaxed = self.relax_edge(path_cost, path_from, a, b, weight) or any_relaxed
        return any_relaxed

    def dag_minimum_path(self):
        post_order_reverse = self.topological_order(0)
        cost, path_from = self._initialize_alg_lists()

        for v in post_order_reverse:
            self.relax_vertice(cost, path_from, v)

        return cost, path_from

    def _initialize_alg_lists(self, vert_init=0):
        cost = [float("inf")] * self.size
        cost[vert_init] = 0
        path_from = [None] * self.size

        return cost, path_from

    def copy(self):
        g = WeightedDigraph(self.size)
        for i in range(self.size):
            for j, w in self.adj[i]:
                g.add_edge(i, j, w)
        return g


def path_from_to_edges(path_from):
    edges = []
    for i in range(len(path_from)):
        if path_from[i] is not None:
            edges.append((path_from[i], i))
    return edges
