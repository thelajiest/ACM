#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> mp(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cin >> mp[i][j];
    }

    int len = n + m - 2;

    int ans = 0;
    for (int mask = 0; mask < (1 << len); mask++) {
        if (__builtin_popcount(mask) != (n - 1)) continue;
        std::vector<int> path{mp[0][0]};
        int nowi = 0, nowj = 0;
        for (int i = 0; i < len; i++) {
            if ((mask >> i) & 1)
                nowi++;
            else
                nowj++;
            path.push_back(mp[nowi][nowj]);
        }
        std::sort(begin(path), end(path));
        path.resize(std::unique(begin(path), end(path)) - path.begin());
        if (n + m - 1 == (int)path.size()) ans++;
    }

    std::cout << ans << std::endl;
    return 0;
}