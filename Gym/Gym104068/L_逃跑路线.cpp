#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;

    std::cin >> n >> m >> k;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> cost(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        cost[i] = ((b - a) % k + k) % k;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> col(n);

    for (int i = 0; i < n; i++) {
        if (col[i] == 0) {
            auto dfs = [&](auto&& self, int u, int c) -> bool {
                col[u] = c;
                bool flag = true;
                for (auto v : adj[u]) {
                    if (col[v] == 0)
                        flag &= self(self, v, -c);
                    else if (col[u] == col[v])
                        return false;
                }
                return flag;
            };
            if (!dfs(dfs, i, 1)) {
                std::cout << n << std::endl;
                return 0;
            }
        }
    }
    int eqW = 0, eqB = 0, nW = 0, nB = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] == 1)
            eqW = (eqW + cost[i]) % k, nW++;
        else
            eqB = (eqB + cost[i]) % k, nB++;
    }

    if (k == 2 || eqW == eqB) {
        std::cout << n << std::endl;
        return 0;
    } else if (int diff = ((eqW - eqB) + k) % k;
               ((diff == 1) || (diff == k - 1))) {
        if (eqW == 0 && eqB == k - 1) {
            std::cout << nB << std::endl;
        } else if (eqB == 0 && eqW == k - 1) {
            std::cout << nW << std::endl;
        } else {
            if (eqW < eqB)
                std::cout << nW << std::endl;
            else
                std::cout << nB << std::endl;
        }
        return 0;
    }

    std::cout << 0 << std::endl;
    return 0;
}