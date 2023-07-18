#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;

    std::cin >> n >> m >> k;

    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> dis(n, k + 1), par(n), son(n);
    std::queue<int> Q;
    Q.push(0);
    dis[0] = 0;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (const auto& v : adj[u]) {
            if (dis[v] == k + 1) {
                dis[v] = dis[u] + 1;
                Q.push(v);
                par[v] = u;
                son[u] += 1;
            }
        }
    }

    i64 ans = 0;
    for (int x = 1; x < n; x++) {
        if (dis[x] > k) continue;
        for (const auto& y : adj[x]) {
            if (y == par[x] || par[y] == x) continue;
            ans += (k - dis[x]);
        }
        ans += 1;
        if (son[x] == 0 && (int)adj[x].size() == 1) ans += (k - dis[x]);
    }

    std::cout << ans + 1 << std::endl;
    return 0;
}