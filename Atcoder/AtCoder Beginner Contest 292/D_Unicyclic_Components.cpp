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
        adj[y].push_back(x);
    }

    std::vector<int> vis(n);

    bool flag = true;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            std::set<int> comp;
            auto dfs = [&](auto&& self, int u) -> void {
                vis[u] = 1;
                comp.insert(u);
                for (auto v : adj[u]) {
                    if (!vis[v]) self(self, v);
                }
            };
            dfs(dfs, i);
            int cnt = 0;
            for (auto node : comp) {
                for (auto v : adj[node])
                    if (comp.find(v) != comp.end()) cnt++;
            }
            flag &= (cnt == 2 * int(comp.size()));
        }
    }

    if (flag)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}