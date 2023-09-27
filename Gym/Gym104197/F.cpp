#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    n *= 2;
    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
        deg[x]++, deg[y]++;
    }

    auto solveCir4 = [&](const std::vector<std::vector<int>> &adj) -> i64 {
        i64 ans = 0;
        std::vector<int> kth(n), rk(n);
        std::vector<i64> cnt(n);
        std::vector<std::vector<int>> key(n);
        std::iota(begin(kth), end(kth), 0);
        std::sort(begin(kth), end(kth),
                  [&](auto x, auto y) { return deg[x] < deg[y]; });
        for (int i = 0; i < n; i++) rk[kth[i]] = i;

        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (rk[v] > rk[u]) key[u].emplace_back(v);
            }
        }
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                for (int w : key[v]) {
                    if (rk[w] > rk[u]) {
                        ans += cnt[w]++;
                        if (ans >= 1) ans = 1;
                    }
                }
            }
            for (int v : adj[u]) {
                for (int w : key[v]) {
                    if (rk[w] > rk[u]) --cnt[w];
                }
            }
        }
        return ans;
    };
    auto cnt4 = solveCir4(adj);

    if (cnt4 >= 1)
        std::cout << "2\n";
    else
        std::cout << "3\n";

    return 0;
}