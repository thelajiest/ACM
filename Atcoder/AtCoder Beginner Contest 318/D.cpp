#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adx(n, std::vector<int>(n, -1));
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            std::cin >> adx[i][j + i + 1];
        }
    }
    std::vector<i64> dp(1 << n);

    std::vector<int> t;
    for (int i = 0; i < (1 << n); i++) t.push_back(i);
    std::sort(begin(t), end(t), [&](auto a, auto b) {
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
    for (auto i : t) {
        std::vector<int> vis(n);
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) vis[j] = 1;
        }
        for (int k1 = 0; k1 < n; k1++) {
            for (int k2 = 0; k2 < n; k2++) {
                if (k1 == k2) continue;
                if (vis[k1] == 0 && vis[k2] == 0 && adx[k1][k2] != -1)
                    dp[(i | (1 << k1)) | (1 << k2)] = std::max(
                        dp[(i | (1 << k1)) | (1 << k2)], dp[i] + adx[k1][k2]);
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < (1 << n); i++) ans = std::max(ans, dp[i]);
    std::cout << dp[(1 << n) - 1] << std::endl;
    return 0;
}