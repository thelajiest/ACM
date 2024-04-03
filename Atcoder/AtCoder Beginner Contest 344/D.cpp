#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string T;
    std::cin >> T;

    int n = T.size();

    int m;
    std::cin >> m;
    std::vector<std::vector<std::string>> S(m);
    for (int i = 0; i < m; i++) {
        int a;
        std::cin >> a;
        for (int j = 0; j < a; j++) {
            std::string x;
            std::cin >> x;
            S[i].emplace_back(std::move(x));
        }
    }

    std::vector dp(m, std::vector(n + 1, (int)1E9));

    for (int i = 0; i < m; i++) {
        dp[i][0] = 0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            for (auto s : S[i]) {
                if (j < s.size()) continue;
                auto x = std::string{T.begin() + j - s.size(), T.begin() + j};
                if (x == s) {
                    dp[i][j] = std::min(
                        dp[std::max(0, i - 1)][j - s.size()] + 1, dp[i][j]);
                }
            }
            dp[i][j] = std::min(dp[std::max(0, i - 1)][j], dp[i][j]);
        }
    }

    std::cout << ((dp[m - 1][n] >= 1E9) ? -1 : dp[m - 1][n]) << std::endl;

    return 0;
}