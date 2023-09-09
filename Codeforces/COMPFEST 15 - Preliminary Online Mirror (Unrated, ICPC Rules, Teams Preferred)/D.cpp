#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector a(n, std::vector(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }

    std::vector dp(m - k + 2, std::vector(n, std::vector(k, 0)));
    for (int i = 1; i <= n - k + 1; i++) {
        for (int x = 0; x < n; x++) {
            for (int y = i - 1; y <= i + k - 2; y++)
                dp[i][x][y] = std::max(dp[i][x][y],
                                       dp[i - 1][x][y - 1 - (i - 1)] + a[x][y]);
        }
    }
    return 0;
}