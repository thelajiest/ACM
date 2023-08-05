#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, D;
    std::cin >> N >> D;

    std::vector<std::vector<char>> s(N);
    for (int i = 0; i < N; i++) {
        std::string _;
        std::cin >> _;
        s[i] = {_.begin(), _.end()};
    }
    int ans = 0;
    for (int l = 0; l < D; l++) {
        for (int r = l; r < D; r++) {
            bool ok = true;
            for (int i = 0; i < N; i++) {
                for (int t = l; t <= r; t++) {
                    if (s[i][t] != 'o') ok = false;
                }
            }
            if (ok) ans = std::max(ans, r - l + 1);
        }
    }

    std::cout << ans << std::endl;

    return 0;
}