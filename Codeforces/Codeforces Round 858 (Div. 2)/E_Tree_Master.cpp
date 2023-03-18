#include <bits/extc++.h>
#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> adj(n);
    std::vector<int> par(n);
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        int p;
        std::cin >> p;
        p--;
        adj[p].push_back(i);
        par[i] = p;
    }

    std::unordered_map<i64, i64> record;

    auto dfs = [&](auto&& self, int x, int y) -> i64 {
        if (x < y) std::swap(x, y);
        i64 hashValue = 1LL * x * (n - 1) + y;
        if (record.find(hashValue) != record.end()) return record[hashValue];
        if (x == -1 || y == -1) return 0;
        return record[hashValue] =
                   1LL * a[x] * a[y] + self(self, par[x], par[y]);
    };

    auto query = [&](int x, int y) -> i64 {
        if (x > y) std::swap(x, y);
        i64 ret = 0;
        int bruteTimes = sqrt(n);
        while (bruteTimes--) {
            ret += 1LL * a[x] * a[y];

            x = par[x];
            y = par[y];

            if (x == -1 || y == -1) break;
        }
        if (x == -1 || y == -1) return ret;
        return dfs(dfs, x, y) + ret;
    };

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        std::cout << query(x, y) << '\n';
    }
    return 0;
}