#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj(n), adj2(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj2[y].push_back(x);
    }

    std::vector<int> dis1(n, -1), dis2(n, -1), vis(n, 0);

    dis1[0] = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        vis[u] = 1;
        for (const auto& v : adj[u]) {
            if (!vis[v]) {
                dis1[v] = dis1[u] + 1;
                self(self, v);
            }
        }
    };
    dfs(dfs, 0);

    std::fill(begin(vis), end(vis), 0);
    dis2[0] = 0;
    auto dfs2 = [&](auto&& self, int u) -> void {
        vis[u] = 1;
        for (const auto& v : adj2[u]) {
            if (!vis[v]) {
                dis2[v] = dis2[u] + 1;
                self(self, v);
            }
        }
    };
    dfs2(dfs2, 0);

    int g = 0;
    for (int x = 0; x < n; x++) {
        for (const auto& y : adj[x]) {
            if (dis1[x] == -1 || dis2[y] == -1) continue;
            g = std::gcd(g, dis1[x] + dis2[y] + 1);
        }
    }

    if (g == 0) {
        std::cout << "No" << '\n';
        return;
    }

    while (g % 5 == 0) g /= 5;
    while (g % 2 == 0) g /= 2;

    if (g == 1) {
        std::cout << "Yes" << '\n';
    } else {
        std::cout << "No" << '\n';
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}