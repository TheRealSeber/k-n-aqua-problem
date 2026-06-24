#!/usr/bin/env python3
import math
import sys
from collections import deque

INF = 1e18
EPSILON = 1e-9


class Edge:
    __slots__ = ("to", "cap", "flow", "rev", "cost")

    def __init__(self, to: int, cap: int, flow: int, rev: int, cost: float) -> None:
        self.to = to
        self.cap = cap
        self.flow = flow
        self.rev = rev
        self.cost = cost


G: list[list[Edge]] = []
dist: list[float] = []
prev_v: list[int] = []
prev_e: list[int] = []


def add_edge(u: int, v: int, cap: int, cost: float) -> None:
    G[u].append(Edge(v, cap, 0, len(G[v]), cost))
    G[v].append(Edge(u, 0, 0, len(G[u]) - 1, -cost))


def spfa(s: int, t: int, vertex_count: int) -> bool:
    global dist, prev_v, prev_e
    dist = [INF] * vertex_count
    prev_v = [-1] * vertex_count
    prev_e = [-1] * vertex_count
    in_queue = [False] * vertex_count

    queue: deque[int] = deque([s])
    dist[s] = 0.0
    in_queue[s] = True

    while queue:
        u = queue.popleft()
        in_queue[u] = False

        for ei, edge in enumerate(G[u]):
            residual = edge.cap - edge.flow
            if residual > 0 and dist[u] + edge.cost < dist[edge.to] - EPSILON:
                dist[edge.to] = dist[u] + edge.cost
                prev_v[edge.to] = u
                prev_e[edge.to] = ei
                if not in_queue[edge.to]:
                    queue.append(edge.to)
                    in_queue[edge.to] = True

    return dist[t] < INF


def min_cost_max_flow(s: int, t: int, vertex_count: int) -> tuple[int, float]:
    total_flow = 0
    total_cost = 0.0

    while spfa(s, t, vertex_count):
        add_flow = 2**31 - 1
        v = t
        while v != s:
            u = prev_v[v]
            edge = G[u][prev_e[v]]
            add_flow = min(add_flow, edge.cap - edge.flow)
            v = u

        v = t
        while v != s:
            u = prev_v[v]
            ei = prev_e[v]
            rev = G[u][ei].rev
            G[u][ei].flow += add_flow
            G[v][rev].flow -= add_flow
            total_cost += add_flow * G[u][ei].cost
            v = u

        total_flow += add_flow

    return total_flow, total_cost


def main() -> int:
    data = sys.stdin.buffer.read().split()
    if len(data) < 2:
        return 1

    it = iter(data)
    k = int(next(it))
    n = int(next(it))

    wells: list[tuple[float, float]] = []
    for _ in range(n):
        wells.append((float(next(it)), float(next(it))))

    h = k * n
    houses: list[tuple[float, float]] = []
    for _ in range(h):
        houses.append((float(next(it)), float(next(it))))

    s = 0
    first_well = 1
    first_house = 1 + n
    t = 1 + n + h
    vertex_count = t + 1

    global G
    G = [[] for _ in range(vertex_count)]

    for i in range(n):
        add_edge(s, first_well + i, k, 0.0)

    for i in range(n):
        wx, wy = wells[i]
        for j in range(h):
            hx, hy = houses[j]
            dx = wx - hx
            dy = wy - hy
            add_edge(first_well + i, first_house + j, 1, math.sqrt(dx * dx + dy * dy))

    for j in range(h):
        add_edge(first_house + j, t, 1, 0.0)

    total_flow, total_cost = min_cost_max_flow(s, t, vertex_count)

    if total_flow != h:
        print(
            f"Error: could not assign all houses (flow={total_flow}, expected={h})",
            file=sys.stderr,
        )
        return 1

    print(f"Koszt: {total_cost:.4f}")

    for i in range(n):
        u = first_well + i
        parts = [f"S{i + 1}"]
        for edge in G[u]:
            if first_house <= edge.to < first_house + h and edge.flow == 1:
                parts.append(f"d{edge.to - first_house + 1}")
        print(" ".join(parts))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
