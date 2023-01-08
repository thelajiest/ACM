#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

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

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            auto dfs = [&](auto&& self, int u) -> void {
                vis[u] = 1;
                for (auto v : adj[u]) {
                    if (!vis[v]) self(self, v);
                }
            };
            dfs(dfs, i);
            ans++;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}