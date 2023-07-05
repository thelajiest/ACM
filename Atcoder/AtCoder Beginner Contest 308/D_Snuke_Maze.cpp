#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> mp(n);
    for (int i = 0; i < n; i++) {
        std::string _;
        std::cin >> _;
        mp[i] = {_.begin(), _.end()};
    }

    auto f = [&m](int x, int y) { return m * x + y; };
    auto judge = [&](int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= m) return false;
        return true;
    };

    std::vector<std::vector<int>> adj(f(n - 1, m - 1) + 1);
    std::vector<std::array<int, 2>> d{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            const std::string snuke = "snuke";
            for (int k = 0; k < 5; k++) {
                if (mp[i][j] == snuke[k]) {
                    for (const auto& [dx, dy] : d) {
                        auto x = i + dx;
                        auto y = j + dy;
                        if (judge(x, y) && mp[x][y] == snuke[(k + 1) % 5])
                            adj[f(i, j)].push_back(f(x, y));
                    }
                }
            }
        }
    }
    std::vector<int> vis(f(n - 1, m - 1) + 1, 0);
    auto dfs = [&](auto&& self, int x) -> void {
        vis[x] = 1;
        for (auto y : adj[x]) {
            if (!vis[y]) self(self, y);
        }
    };

    dfs(dfs, 0);
    if (vis.back())
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}