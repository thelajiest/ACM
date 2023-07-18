#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    using Point = std::pair<int, int>;
    Point a, b, c;

    std::cin >> a.first >> a.second;
    std::cin >> b.first >> b.second;
    std::cin >> c.first >> c.second;

    int x1 = b.first - a.first;
    int y1 = b.second - a.second;

    int x2 = c.first - a.first;
    int y2 = c.second - a.second;

    int ans = 0;

    if (1LL * x1 * x2 >= 0) {
        ans += std::min(std::abs(x1), std::abs(x2));
    }

    if (1LL * y1 * y2 >= 0) {
        ans += std::min(std::abs(y1), std::abs(y2));
    }

    std::cout << ans + 1 << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}