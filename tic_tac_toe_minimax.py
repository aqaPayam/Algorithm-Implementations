import sys

sys.setrecursionlimit(2000000)


class Graph:

    def __init__(self, p):
        self.p = p
        self.edges = [[] for _ in range(p)]
        self.color = [0 for _ in range(p)]
        self.visited = [False for _ in range(self.p)]
        # 0 rang nashode 1 abi 2 ghermez

    def add_edge(self, v1, v2):
        self.edges[v1].append(v2)
        self.edges[v2].append(v1)

    def get_not_colored_neighbors(self, v):
        res = []
        for e in self.edges[v]:
            if self.color[e] == 0:
                res.append(e)
        return res

    def get_colored_neighbors(self, v):
        res = []
        for e in self.edges[v]:
            if self.color[e] != 0:
                res.append(e)
        return res

    def isBipartite(self):
        queue = []
        for i in range(self.p):
            if self.color[i] == 0:
                self.color[i] = 1
                queue.append(i)
                while queue:
                    u = queue.pop(0)
                    for v in self.get_not_colored_neighbors(u):
                        self.color[v] = 3 - self.color[u]
                        queue.append(v)
                    for v in self.get_colored_neighbors(u):
                        if self.color[v] == self.color[u]:
                            return False

        return True

    def countComp(self):
        res = 0
        for v in range(self.p):
            if not self.visited[v]:
                self.dfs(v)
                res += 1

        return res

    def dfs(self, v):
        self.visited[v] = True

        for i in self.edges[v]:
            if not self.visited[i]:
                self.dfs(i)


n, m = map(int, input().split())
g = Graph(n)
for i in range(m):
    v1, v2 = map(int, input().split())
    g.add_edge(v1 - 1, v2 - 1)

print((2 ** (g.countComp() - 1)) % (10 ** 9 + 7) if g.isBipartite() else 0)
