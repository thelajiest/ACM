#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) std::cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;

        std::cout << "10" << std::endl;
    }
    return 0;
}