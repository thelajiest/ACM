#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> vis(n);
    std::vector<std::vector<int>> adj(n);

    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        x--;
        adj[0].push_back(x);
    }

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        if (u == n - 1) {
            exit(0);
        }
        vis[u] = 1;
        for (auto v : adj[u]) {
            if (!vis[v]) {
                std::cout << v + 1 << std::endl;
                if (v == n - 1) {
                    std::string s;
                    std::cin >> s;
                    // std::cout.flush();
                    // exit(0);
                } else {
                    int k;
                    std::cin >> k;
                    std::vector<int> in(k);
                    for (int i = 0; i < k; i++) {
                        std::cin >> in[i];
                        in[i]--;
                    }
                    if (adj[v].empty()) adj[v] = in;
                }
                self(self, v, u);
            }
        }
        std::cout << fa + 1 << std::endl;
        int k;
        std::cin >> k;
        std::vector<int> in(k);
        for (int i = 0; i < k; i++) {
            std::cin >> in[i];
            in[i]--;
        }
        return;
    };

    dfs(dfs, 0, -1);
    return 0;
}