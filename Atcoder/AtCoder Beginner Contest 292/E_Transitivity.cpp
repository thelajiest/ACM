#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
    }

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        std::vector<int> vis(n);
        auto dfs = [&](auto&& self, int u) -> void {
            vis[u] = 1;
            for (const auto& v : adj[u]) {
                if (vis[v]) continue;
                self(self, v);
            }
        };

        dfs(dfs, i);
        cnt += std::count(vis.begin(), vis.end(), 1) - 1;
    }

    std::cout << cnt - m << std::endl;
    return 0;
}