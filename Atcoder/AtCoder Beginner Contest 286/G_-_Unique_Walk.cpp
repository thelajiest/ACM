#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;

    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);

    std::vector<std::pair<int, int>> E(m);

    for (auto& [u, v] : E) {
        std::cin >> u >> v;
        u--, v--;
    }

    int k;
    std::cin >> k;

    std::vector<int> sig(m);
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        x--;
        sig[x] = 1;
    }

    for (int i = 0; i < m; i++) {
        if (!sig[i]) {
            auto [u, v] = E[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    std::vector<int> col(n, -1);

    int p = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] == -1) {
            auto dfs = [&](auto&& self, int u) -> void {
                col[u] = p;
                for (const auto& v : adj[u]) {
                    if (col[v] == -1) self(self, v);
                }
            };
            dfs(dfs, i);
            p++;
        }
    }

    std::vector<int> deg(p);
    for (int i = 0; i < m; i++) {
        if (sig[i]) {
            auto [u, v] = E[i];
            deg[col[u]]++;
            deg[col[v]]++;
        }
    }

    int h = 0;
    for (int i = 0; i < p; i++) {
        h += (deg[i] % 2);
    }

    if (h == 2 || h == 0)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}