import random
import networkx as nx
import heapq
import matplotlib.pyplot as plt


class UnionFind:
    def __init__(self, size):
        self.parents = list(range(size))
        self.rank = [0 for x in range(size)]

    def find(self, i):
        update_parents = []
        while i != self.parents[i]:
            update_parents.append(i)
            i = self.parents[i]

        for j in update_parents:
            self.parents[j] = i

        return i

    def union(self, i, j):
        irep = self.find(i)
        jrep = self.find(j)

        if irep == jrep:
            return

        if self.rank[irep] > self.rank[jrep]:
            self.parents[jrep] = irep
        else:
            self.parents[irep] = jrep
            if self.rank[irep] == self.rank[jrep]:
                self.rank[jrep] += 1


class UnionFindNaive:
    def __init__(self, size):
        self.parents = list(range(size))

    def find(self, i):
        while i != self.parents[i]:
            i = self.parents[i]
        return i

    def union(self, i, j):
        irep = self.find(i)
        jrep = self.find(j)

        if irep == jrep:
            return

        self.parents[irep] = jrep


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


def generate_random_tree(n_vert):
    g = WeightedGraph(n_vert)

    for i in range(1, n_vert):
        j = random.randint(0, i - 1)
        g.add_edge(j, i, random.uniform(0, 1))

    return g


class WeightedGraph:
    def __init__(self, size):
        self.adj = [None] * size
        for i in range(size):
            self.adj[i] = []
        self.size = size
        self.qtd_edge = 0
        self.edges_list = []

    def add_edge(self, vert0, vert1, edge_weight, check=False):
        if check:
            for adj_vert, _ in self.adj[vert0]:
                if adj_vert == vert1:
                    return False

        self.adj[vert0].append((vert1, edge_weight))
        self.adj[vert1].append((vert0, edge_weight))

        if vert0 < vert1:
            self.edges_list.append((edge_weight, vert0, vert1))
        else:
            self.edges_list.append((edge_weight, vert1, vert0))

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
        G = nx.Graph()

        G.add_nodes_from([x for x in range(self.size)])

        for i in range(self.size):
            for j, w in self.adj[i]:
                G.add_edge(i, j, weight=w)

        return G

    def plot(
        self,
        ax,
        layout=nx.kamada_kawai_layout,
        pos=None,
        edge_color="black",
        plot_vertices=True,
        edge_weights=True,
        width=1.0,
    ):
        G = self.to_nx_graph()

        if pos is None:
            pos = layout(G)

        if plot_vertices:
            nx.draw(
                G,
                pos,
                with_labels=True,
                node_color="lightblue",
                node_size=500,
                width=width,
                edge_color=edge_color,
                ax=ax,
            )
        else:
            nx.draw_networkx_edges(G, pos, width=width, alpha=0.5, edge_color=edge_color, ax=ax)

        if edge_weights:
            labels = {}
            for edge in G.edges:
                labels[edge] = G.edges[edge]["weight"]
            nx.draw_networkx_edge_labels(G, pos, ax=ax, edge_labels=labels)

        return pos

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

    def prim_lazy(self, plot_at_steps=None, output_folder=None):
        mst = WeightedGraph(self.size)

        added = [False] * self.size
        added[0] = True

        crossing_edges = []

        add_edges(crossing_edges, 0, self.adj[0], added)

        qtd_added_edges = 0
        while len(crossing_edges) > 0:
            w, vert_a, vert_b = heapq.heappop(crossing_edges)
            if not added[vert_b]:
                added[vert_b] = True
                mst.add_edge(vert_a, vert_b, w)
                add_edges(crossing_edges, vert_b, self.adj[vert_b], added)
                qtd_added_edges += 1

                if plot_at_steps is not None and qtd_added_edges in plot_at_steps:
                    fig, ax = plt.subplots(figsize=(7, 7))
                    pos = self.plot(ax, edge_color="gray", edge_weights=False, plot_vertices=False)
                    mst.plot(ax, pos=pos, edge_color="red", edge_weights=False, plot_vertices=False, width=2.5)
                    ax.set_title(f"Prim - Step {qtd_added_edges}")
                    plt.savefig(f"{output_folder}/prim_step_{qtd_added_edges}.pdf", bbox_inches="tight")
                    plt.close()

        return mst

    def total_cost(self):
        cost = 0
        for i in range(self.size):
            for vert, w in self.adj[i]:
                cost += w
        cost /= 2
        return cost

    def kruskal(self, naive_union_find=False, plot_at_steps=None, output_folder=None):
        edges_heap = []
        for edge in self.edges_list:
            heapq.heappush(edges_heap, edge)

        if naive_union_find:
            connected_components = UnionFindNaive(self.size)
        else:
            connected_components = UnionFind(self.size)

        mst = WeightedGraph(self.size)
        qtd_added_verts = 0

        while len(edges_heap) > 0 and qtd_added_verts < self.size - 1:
            w, a, b = heapq.heappop(edges_heap)

            if connected_components.find(a) == connected_components.find(b):
                continue

            connected_components.union(a, b)

            mst.add_edge(a, b, w)
            qtd_added_verts += 1

            if plot_at_steps is not None and qtd_added_verts in plot_at_steps:
                fig, ax = plt.subplots(figsize=(7, 7))
                pos = self.plot(ax, edge_color="gray", edge_weights=False, plot_vertices=False)
                mst.plot(ax, pos=pos, edge_color="red", edge_weights=False, plot_vertices=False, width=2.5)
                ax.set_title(f"Kruskal - Step {qtd_added_verts}")
                plt.savefig(f"{output_folder}/kruskal_step_{qtd_added_verts}.pdf", bbox_inches="tight")
                plt.close()

        return mst

    def kruskal_set(self):
        edges_heap = []
        for edge in self.edges_list:
            heapq.heappush(edges_heap, edge)

        connected_components = []
        for i in range(self.size):
            connected_components.append(set([i]))

        mst = WeightedGraph(self.size)
        qtd_added_verts = 0
        while len(edges_heap) > 0 and qtd_added_verts < self.size - 1:
            w, a, b = heapq.heappop(edges_heap)

            if b in connected_components[a]:
                continue

            if len(connected_components[b]) > len(connected_components[a]):
                a, b = b, a

            connected_components[a].update(connected_components[b])
            for v in connected_components[a]:
                connected_components[v] = connected_components[a]

            mst.add_edge(a, b, w)
            qtd_added_verts += 1

        return mst

    def copy(self):
        g = WeightedGraph(self.size)
        for i in range(self.size):
            for vert, w in self.adj[i]:
                g.add_edge(i, vert, w)
        return g


def add_edges(crossing_edges, vert_a, edges, added):
    for vert_b, w in edges:
        if not added[vert_b]:
            heapq.heappush(crossing_edges, (w, vert_a, vert_b))
