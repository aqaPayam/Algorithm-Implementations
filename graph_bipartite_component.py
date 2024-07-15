import math
from queue import Queue


class Graph:

    def __init__(self, CeNum, CSNUm):
        self.p = n + m + 2
        self.graph = [[0 for _ in range(self.p)] for _ in range(self.p)]
        for i in range(1, n + 1):
            for j in range(n + 1, n + m + 1):
                self.set_edge(i, j, math.inf)

    def set_edge(self, v1, v2, w):
        self.graph[v1][v2] = w

    def bfs(self, s, t, parent):
        visited = [False] * self.p
        q = Queue()
        q.put(s)
        visited[s] = True
        parent[s] = -1

        while not q.empty():
            u = q.get()

            for v in range(self.p):
                if not visited[v] and self.graph[u][v] > 0:

                    q.put(v)
                    visited[v] = True
                    parent[v] = u

                    if v == t:
                        return True

        return False

    def max_flow(self, source, sink):
        parent = [-1] * self.p

        max_flow = 0

        while self.bfs(source, sink, parent):

            path_flow = float("inf")

            s = sink
            while s != source:
                path_flow = min(path_flow, self.graph[parent[s]][s])
                s = parent[s]

            max_flow += path_flow

            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]

        return max_flow


n, m, k = map(int, input().split())
g = Graph(CeNum=n, CSNUm=m)

for i in range(k):
    v1, v2 = map(int, input().split())
    g.set_edge(v1, v2 + n, 0)

ce = list(map(int, input().split()))
cs = list(map(int, input().split()))

for i in range(1, n + 1):
    g.set_edge(0, i, ce[i - 1])

for i in range(1, m + 1):
    g.set_edge(n + i, n + m + 1, cs[i - 1])

print(sum(ce) + sum(cs) - g.max_flow(0, n + m + 1))
