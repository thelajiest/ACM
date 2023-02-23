#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> E(m);
    std::vector<int> deg(n);
    for (auto& [u, v] : E) {
        std::cin >> u >> v;
        u--, v--;
        if (u > v) std::swap(u, v);
        deg[u]++, deg[v]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] < n - 1) {
            std::cout << 2 << '\n';
            for (const auto& [u, v] : E) {
                if (u == i || v == i)
                    std::cout << 1 << " ";
                else
                    std::cout << 2 << " ";
            }
            std::cout << '\n';
            return;
        }
    }

    std::cout << 3 << '\n';
    for (const auto& [u, v] : E) {
        if (u == 0) {
            if (v == 1)
                std::cout << 3 << " ";
            else
                std::cout << 2 << " ";
        } else
            std::cout << 1 << " ";
    }
    std::cout << '\n';
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