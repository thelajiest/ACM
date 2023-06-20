#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);

    for (auto& [x, y] : a) std::cin >> x >> y;
    std::vector<std::array<i64, 2>> dp(n);

    if (a[0].first == 0) {
        dp[0][0] = std::max<i64>(dp[0][0], 1LL * a[0].second);
        dp[0][1] = 0;
    } else {
        dp[0][1] = std::max<i64>(dp[0][1], 1LL * a[0].second);
        dp[0][0] = 0;
    }

    for (int i = 1; i < n; i++) {
        auto [curx, cury] = a[i];
        if (curx == 0) {
            dp[i][0] = std::max({dp[i - 1][0] + cury, dp[i - 1][1] + cury,
                                 dp[i - 1][0], dp[i][0]});
            dp[i][1] = std::max(dp[i][1], dp[i - 1][1]);
        } else {
            dp[i][0] = std::max(dp[i - 1][0], dp[i][0]);
            dp[i][1] = std::max({dp[i - 1][0] + cury, dp[i][1], dp[i - 1][1]});
        }
    }

    std::cout << std::max(dp[n - 1][0], dp[n - 1][1]);
    return 0;
}