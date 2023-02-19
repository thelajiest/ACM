#include <bits/stdc++.h>

using i64 = std::int64_t;

struct MCFGraph {
    struct Edge {
        int v, c, f;
        Edge(int v, int c, int f) : v(v), c(c), f(f) {}
    };
    const int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<i64> h, dis;
    std::vector<int> pre;
    bool dijkstra(int s, int t) {
        dis.assign(n, std::numeric_limits<i64>::max());
        pre.assign(n, -1);
        std::priority_queue<std::pair<i64, int>,
                            std::vector<std::pair<i64, int>>,
                            std::greater<std::pair<i64, int>>>
            que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            i64 d = que.top().first;
            int u = que.top().second;
            que.pop();
            if (dis[u] < d) continue;
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<i64>::max();
    }
    MCFGraph(int n) : n(n), g(n) {}
    void addEdge(int u, int v, int c, int f) {
        if (f < 0) {
            g[u].push_back(e.size());
            e.emplace_back(v, 0, f);
            g[v].push_back(e.size());
            e.emplace_back(u, c, -f);
        } else {
            g[u].push_back(e.size());
            e.emplace_back(v, c, f);
            g[v].push_back(e.size());
            e.emplace_back(u, 0, -f);
        }
    }
    std::pair<int, i64> flow(int s, int t) {
        int flow = 0;
        i64 cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
                aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += i64(aug) * h[t];
        }
        return std::make_pair(flow, cost);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 0 for S; 1-n for boys, n+1-2n for girls ; 2n+1 for T

    int n;
    std::cin >> n;

    int S = 0, T = 2 * n + 1;

    MCFGraph MCF(2 * n + 2);

    std::vector<int> a(n + 1), p(n + 1), b(n + 1), q(n + 1);

    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) std::cin >> q[i];

    for (int i = 1; i <= n; i++) {
        MCF.addEdge(S, i, 1, 0);
    }

    for (int i = n + 1; i <= 2 * n; i++) {
        MCF.addEdge(i, T, 1, 0);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val = ((q[j] - a[i] < 0) ? 0 : q[j] - a[i]) +
                      ((p[i] - b[j] < 0) ? 0 : p[i] - b[j]);
            MCF.addEdge(i, n + j, 1, val);
        }
    }

    auto [flow, cost] = MCF.flow(S, T);

    std::cout << cost << std::endl;

    return 0;
}