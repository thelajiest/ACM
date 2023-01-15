#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::vector<i64> val(n + 1);

    for (int i = 1; i <= n; i++) {
        val[i] = val[i - 1] + a[(i + 1) / 2];
    }

    constexpr i64 INF = std::numeric_limits<i64>::max() / 2.0;
    std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(n + 1, -INF));

    dp[1][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j + 1] = std::max(dp[i + 1][j + 1], dp[i][j]);
            dp[i + 1][0] = std::max(dp[i][j] + val[j], dp[i + 1][0]);
        }
    }

    i64 ans = 0;

    for (int i = 0; i <= n; i++) {
        ans = std::max(ans, dp[n][i] + val[i]);
    }

    std::cout << ans << std::endl;
    return 0;
}