#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::tuple<int, i64, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        i64 w;
        std::cin >> x >> y >> w;
        x--, y--;
        adj[x].emplace_back(y, w, 0);
        adj[y].emplace_back(x, w, 0);
    }

    std::vector<int> vis(n), siz(n), dfn(n);
    std::vector<i64> dep(n);
    int cnt = 0;

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        vis[u] = 1;
        dfn[u] = cnt++;
        siz[u] = 1;
        for (auto& [v, w, back] : adj[u]) {
            if (vis[v]) {
                if (v != fa) back = 1;
                continue;
            } else {
                dep[v] = dep[u] + w;
                self(self, v, u);
                siz[u] += siz[v];
            }
        }
    };
    auto checkSon = [&](int x, int y) -> bool {
        // whether x is a son of y
        return dfn[y] <= dfn[x] && dfn[x] <= dfn[y] + siz[y] - 1;
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(dfs, i, -1);
        }
    }

    i64 d = 0;
    std::vector<std::tuple<int, int, i64>> backEdge;
    for (int x = 0; x < n; x++) {
        for (const auto& [y, w, back] : adj[x]) {
            if (back && x < y) {
                backEdge.emplace_back(x, y, w);
            }
        }
    }

    int size = backEdge.size();
    for (int i = 0; i < size; i++) {
        auto [x1, y1, w1] = backEdge[i];
        if (dfn[x1] > dfn[y1]) std::swap(x1, y1);
        if (dep[y1] > dep[x1]) d = std::gcd(d, dep[y1] - dep[x1] + w1);
        for (int j = 0; j < size; j++) {
            if (i == j) continue;
            auto [x2, y2, w2] = backEdge[j];
            if (dfn[x2] > dfn[y2]) std::swap(x2, y2);
            if (checkSon(y1, y2) && checkSon(x1, x2) && checkSon(y2,  x1))
                d = std::gcd(d, 2LL * (dep[y2] - dep[x1]));
            if (checkSon(y2, y1) && checkSon(x2, x1) && checkSon(y1, x2))
                d = std::gcd(d, 2LL * (dep[y1] - dep[x2]));
            if (checkSon(y2, y1) && checkSon(x1, x2))
                d = std::gcd(d, 2LL * (dep[y1] - dep[x1]));
            if (checkSon(y1, y2) && checkSon(x2, x1))
                d = std::gcd(d, 2LL * (dep[y2] - dep[x2]));
        }
    }

    std::cout << d << std::endl;

    return 0;
}