#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

static const double INF     = 1e18;
static const double EPSILON = 1e-9;

struct Edge {
    int    to, cap, flow, rev;
    double cost;
};

std::vector<std::vector<Edge>> G;
std::vector<double>            dist;
std::vector<int>               prevV, prevE;

void addEdge(int u, int v, int cap, double cost) {
    G[u].push_back({v, cap, 0, (int)G[v].size(), cost});
    G[v].push_back({u, 0,   0, (int)G[u].size() - 1, -cost});
}

bool spfa(int s, int t, int V) {
    dist.assign(V, INF);
    prevV.assign(V, -1);
    prevE.assign(V, -1);
    std::vector<bool> inQueue(V, false);

    std::queue<int> Q;
    dist[s] = 0.0;
    Q.push(s);
    inQueue[s] = true;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inQueue[u] = false;

        for (int ei = 0; ei < (int)G[u].size(); ei++) {
            const Edge &e        = G[u][ei];
            int         residual = e.cap - e.flow;
            if (residual > 0 && dist[u] + e.cost < dist[e.to] - EPSILON) {
                dist[e.to] = dist[u] + e.cost;
                prevV[e.to] = u;
                prevE[e.to] = ei;
                if (!inQueue[e.to]) {
                    Q.push(e.to);
                    inQueue[e.to] = true;
                }
            }
        }
    }

    return dist[t] < INF;
}

std::pair<int, double> minCostMaxFlow(int s, int t, int V) {
    int    totalFlow = 0;
    double totalCost = 0.0;

    while (spfa(s, t, V)) {
        // Find bottleneck on the s->t path
        int addFlow = INT_MAX;
        for (int v = t; v != s; v = prevV[v]) {
            int u = prevV[v];
            addFlow = std::min(addFlow, G[u][prevE[v]].cap - G[u][prevE[v]].flow);
        }

        // Push flow along path and accumulate cost
        for (int v = t; v != s; v = prevV[v]) {
            int u  = prevV[v];
            int ei = prevE[v];
            int r  = G[u][ei].rev;
            G[u][ei].flow += addFlow;
            G[v][r].flow  -= addFlow;
            totalCost     += (double)addFlow * G[u][ei].cost;
        }

        totalFlow += addFlow;
    }

    return {totalFlow, totalCost};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k, n;
    std::cin >> k >> n;

    std::vector<std::pair<double, double>> wells(n);
    for (int i = 0; i < n; i++)
        std::cin >> wells[i].first >> wells[i].second;

    int h = k * n;
    std::vector<std::pair<double, double>> houses(h);
    for (int j = 0; j < h; j++)
        std::cin >> houses[j].first >> houses[j].second;

    // Node numbering:
    //   s       = 0
    //   well i  = 1 + i           (i in [0, n))
    //   house j = 1 + n + j       (j in [0, h))
    //   t       = 1 + n + h
    int s          = 0;
    int firstWell  = 1;
    int firstHouse = 1 + n;
    int t          = 1 + n + h;
    int V          = t + 1;

    G.assign(V, std::vector<Edge>());

    // s -> wells (capacity k, cost 0)
    for (int i = 0; i < n; i++)
        addEdge(s, firstWell + i, k, 0.0);

    // wells -> houses (capacity 1, cost = Euclidean distance)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < h; j++) {
            double dx = wells[i].first  - houses[j].first;
            double dy = wells[i].second - houses[j].second;
            addEdge(firstWell + i, firstHouse + j, 1, std::sqrt(dx * dx + dy * dy));
        }
    }

    // houses -> t (capacity 1, cost 0)
    for (int j = 0; j < h; j++)
        addEdge(firstHouse + j, t, 1, 0.0);

    auto [totalFlow, totalCost] = minCostMaxFlow(s, t, V);

    if (totalFlow != h) {
        std::cerr << "Error: could not assign all houses (flow=" << totalFlow
                  << ", expected=" << h << ")\n";
        return 1;
    }

    // Output assignment: for each well, list the houses with flow == 1
    for (int i = 0; i < n; i++) {
        int u = firstWell + i;
        std::cout << "S" << (i + 1);
        for (const Edge &e : G[u]) {
            if (e.to >= firstHouse && e.to < firstHouse + h && e.flow == 1) {
                std::cout << " d" << (e.to - firstHouse + 1);
            }
        }
        std::cout << "\n";
    }

    return 0;
}
