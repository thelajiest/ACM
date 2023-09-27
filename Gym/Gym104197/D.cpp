#include <bits/stdc++.h>

using i64 = std::int64_t;
void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    std::vector parity(n, std::vector(n, 0));

    std::vector<std::pair<int, int>> E;
    for (int i = 0; i < n; i++) {
        std::string _;
        std::cin >> _;
        for (int j = 0; j < n; j++) {
            parity[i][j] = _[j] - '0';
            if (parity[i][j]) {
                if (i < j) E.emplace_back(i, j);
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        auto bfs = [&](int s) -> std::vector<int> {
            std::vector<int> vis(n);
            std::vector<int> dis(n, -1);
            vis[s] = 1, dis[s] = 0;
            std::queue<int> Q;
            Q.push(s);

            while (!Q.empty()) {
                auto u = Q.front();
                Q.pop();
                for (const auto& v : adj[u]) {
                    if (vis[v]) continue;
                    vis[v] = 1;
                    dis[v] = dis[u] + 1;
                    Q.push(v);
                }
            }

            return dis;
        };
        auto dis = bfs(i);
        for (int j = 0; j < n; j++) {
            if (parity[i][j] != dis[j] % 2 || dis[j] == -1) {
                std::cout << "NO\n";
                return;
            }
        }
    }

    std::cout << "YES\n";
    std::cout << E.size() << '\n';
    for (const auto& [x, y] : E) {
        std::cout << x + 1 << " " << y + 1 << '\n';
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