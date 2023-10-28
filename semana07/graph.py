class Graph:
    def __init__(self, size):
        self.adj = [None] * size
        for i in range(size):
            self.adj[i] = []
        self.size = size

    def add_edge(self, vert0, vert1, check=False):
        if check:
            for adj_vert in self.adj[vert0]:
                if adj_vert == vert1:
                    return False

        self.adj[vert0].append(vert1)
        self.adj[vert1].append(vert0)
        return True

    def bfs(self, vert_start):
        queue = []
        queue.append(vert_start)
        marcado = [False] * self.size
        marcado[vert_start] = True

        aresta_final = [-1] * self.size

        while len(queue) > 0:
            v = queue.pop(0)
            for w in self.adj[v]:
                if not marcado[w]:
                    aresta_final[w] = v
                    marcado[w] = True
                    queue.append(w)

        return marcado, aresta_final

    def dfs(self, vert_start):
        queue = []
        queue.append(vert_start)
        marcado = [False] * self.size
        marcado[vert_start] = True

        aresta_final = [-1] * self.size

        while len(queue) > 0:
            v = queue.pop()
            for w in self.adj[v]:
                if not marcado[w]:
                    aresta_final[w] = v
                    marcado[w] = True
                    queue.append(w)

        return marcado, aresta_final

    def search(self, vert_start):
        pass

    def build_path(self, aresta_final, vert_end):
        path = [vert_end]
        cur_vert = vert_end
        while aresta_final[cur_vert] != -1:
            cur_vert = aresta_final[cur_vert]
            path.append(cur_vert)

        return path[::-1]
