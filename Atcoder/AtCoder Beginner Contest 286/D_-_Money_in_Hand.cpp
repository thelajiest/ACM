#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(x + 1));

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int a, b;

        std::cin >> a >> b;

        for (int j = 0; j <= x; j++) {
            for (int t = 0; t <= b; t++) {
                if (j + a * t > x) continue;
                dp[i][j + a * t] |= dp[i - 1][j];
            }
        }
    }

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        ans |= dp[i][x];
    }

    if (ans) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}