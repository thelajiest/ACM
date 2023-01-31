#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    i64 x;
    std::cin >> x;

    if (x % 2 == 1) {
        std::cout << -1 << '\n';
        return;
    }

    i64 half = x / 2;
    if (half & x) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << half + x << " " << half << '\n';

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