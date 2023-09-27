#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int c, n;
    std::cin >> c >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::vector dp(c + 1, std::vector(c + 1, std::vector(2, 0)));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int c1 = 0; c1 <= c; c1++) {
            for (int c2 = 0; c2 <= c; c2++) {
                if (c1 + a[i] <= c)
                    dp[c1 + a[i]][c2][(i + 1) & 1] |= dp[c1][c2][i & 1];
                if (c2 + a[i] <= c)
                    dp[c1][c2 + a[i]][(i + 1) & 1] |= dp[c1][c2][i & 1];
                dp[c1][c2][(i + 1) & 1] |= dp[c1][c2][i & 1];
            }
        }
    }

    std::vector<std::pair<int, int>> ans;
    for (int c1 = 0; c1 <= c; c1++) {
        for (int c2 = 0; c2 <= c1; c2++) {
            if (dp[c1][c2][n & 1]) {
                if (c1 >= c2) ans.emplace_back(c1, c2);
            }
        }
    }

    std::sort(begin(ans), end(ans), [&](auto a, auto b) {
        if (a.first + a.second > b.first + b.second) return true;
        if (a.first + a.second < b.first + b.second) return false;

        return abs(a.first - a.second) < abs(b.first - b.second);
    });
    std::cout << ans[0].first << " " << ans[0].second << std::endl;

    return 0;
}