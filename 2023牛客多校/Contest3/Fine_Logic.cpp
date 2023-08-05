#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;

    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        deg[y]++;
    }

    std::queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) Q.push(i);
    }

    std::vector<int> tp;
    while (!Q.empty()) {
        int u = Q.front();
        tp.push_back(u);
        Q.pop();
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) Q.push(v);
        }
    }

    if (tp.size() == n) {
        std::cout << 1 << '\n';
        for (int i = 0; i < n; i++) {
            std::cout << tp[i] + 1 << " \n"[i == n - 1];
        }
    } else {
        std::cout << 2 << '\n';
        for (int i = 0; i < n; i++) {
            std::cout << i + 1 << " \n"[i == n - 1];
        }
        for (int i = 0; i < n; i++) {
            std::cout << n - i << " \n"[i == n - 1];
        }
    }
    return 0;
}