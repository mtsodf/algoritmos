class Digraph:
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

    def __str__(self):
        s = ""
        for i in range(self.size):
            s += f"{i}: {self.adj[i]}\n"
        return s

    def topological_order(self, vert_start):
        marcado = [False] * self.size
        visitado = []
        self.dfs(vert_start, marcado, visitado)
        for i in range(self.size):
            if not marcado[i]:
                self.dfs(i, marcado, visitado)

        visitado = visitado[::-1]
        return visitado
