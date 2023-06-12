#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back({v, 1});
        adj[v].push_back({u, 1});
    }

    std::vector<std::pair<int, int>> g(k);

    int hMax = 0;
    for (auto& [p, h] : g) {
        std::cin >> p >> h;
        p--;
        hMax = std::max(hMax, h);
    }
    for (const auto& [p, h] : g) {
        adj[n].push_back({p, hMax - h});
        adj[p].push_back({n, hMax - h});
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        Q;

    Q.push({0, n});

    std::vector<int> dis(n + 1, hMax + 1), vis(n + 1);
    dis[n] = 0;

    while (!Q.empty()) {
        auto [d, u] = Q.top();
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                Q.push({dis[v], v});
            }
        }
    }

    std::vector<int> ans;
    for (int i = 0; i < n; i++)
        if (dis[i] <= hMax) ans.push_back(i);

    std::cout << ans.size() << std::endl;
    for (auto p : ans) std::cout << p + 1 << " ";

    return 0;
}