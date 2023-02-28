#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> siz(n), vis(n), par(n, -2);

    auto countSiz = [&](auto&& self, int u, int fa) -> int {
        siz[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v] || v == fa) continue;
            siz[u] += self(self, v, u);
        }
        return siz[u];
    };

    auto searchCentroid = [&](auto&& self, int u, int fa, int halfSiz) -> int {
        for (auto v : adj[u]) {
            if (v == fa || vis[v]) continue;
            if (siz[v] > halfSiz) return self(self, v, u, halfSiz);
        }
        return u;
    };

    auto buildDfs = [&](auto&& self, int u) -> int {
        vis[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            int centroid = searchCentroid(searchCentroid, v, -1,
                                          countSiz(countSiz, v, -1) / 2);
            auto rt = self(self, centroid);
            par[rt] = u;
        }
        return u;
    };

    int S =
        searchCentroid(searchCentroid, 0, -1, countSiz(countSiz, 0, -1) / 2);

    buildDfs(buildDfs, S);

    for (int i = 0; i < n; i++) std::cout << par[i] + 1 << " \n"[i == n - 1];

    return 0;
}