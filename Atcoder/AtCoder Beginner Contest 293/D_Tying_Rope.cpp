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
        char a, b;
        std::cin >> x >> a >> y >> b;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int ans1 = 0, ans2 = 0;
    std::vector<int> vis(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            std::set<int> node;
            auto dfs = [&](auto&& self, int u) -> void {
                vis[u] = 1;
                node.insert(u);
                for (const auto& v : adj[u]) {
                    if (!vis[v]) self(self, v);
                }
            };
            dfs(dfs, i);
            int cntEdge = 0;
            int cntNode = node.size();
            for (auto u : node) {
                for (auto v : adj[u]) {
                    if (node.find(v) != node.end()) cntEdge++;
                }
            }
            assert(cntEdge % 2 == 0);
            cntEdge /= 2;
            if (cntEdge == cntNode)
                ans1++;
            else
                ans2++;
        }
    }

    std::cout << ans1 << " " << ans2 << std::endl;

    return 0;
}