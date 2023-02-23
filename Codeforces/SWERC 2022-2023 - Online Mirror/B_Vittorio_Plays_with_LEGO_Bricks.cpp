#include <bits/stdc++.h>

using i64 = std::int64_t;

constexpr i64 INF = std::numeric_limits<i64>::max() / 3.0;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, h;
    std::cin >> n >> h;

    std::vector<int> x(n);
    for (int i = 0; i < n; i++) std::cin >> x[i];

    std::vector<std::vector<int>> cost(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            cost[i][j] = std::max(0, h + 1 - (x[j] - x[i] + 1) / 2);
    }
    std::vector<std::vector<i64>> dp(n, std::vector<i64>(n, INF));
    for (int i = 0; i < n; i++) dp[i][i] = h;

    for (int l = n - 1; l >= 0; l--) {
        for (int r = l + 1; r < n; r++) {
            for (int k = l; k + 1 <= r; k++)
                dp[l][r] =
                    std::min(dp[l][r], dp[l][k] + dp[k + 1][r] - cost[l][r]);
        }
    }
    std::cout << dp[0][n - 1] << std::endl;

    return 0;
}