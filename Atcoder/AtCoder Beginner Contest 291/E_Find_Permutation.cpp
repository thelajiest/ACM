#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);

    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        deg[y]++;
    }

    std::queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) Q.push(i);
    }

    std::vector<int> tp;

    while (!Q.empty()) {
        if (Q.size() > 1) {
            std::cout << "No" << std::endl;
            return 0;
        }
        auto u = Q.front();
        tp.push_back(u);
        Q.pop();
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) Q.push(v);
        }
    }

    std::cout << "Yes" << std::endl;
    std::vector<int> ans(n);
    int p = 1;
    for (auto it : tp) {
        ans[it] = p++;
    }

    for (int i = 0; i < n; i++) std::cout << ans[i] << " \n"[i == n - 1];

    return 0;
}