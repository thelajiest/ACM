#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    i64 x, y;
    i64 a, b;
    std::cin >> x >> y;
    std::cin >> a >> b;

    i64 nowx = a - x, nowy = b - y;

    if (nowy < 0 || nowy < nowx) {
        std::cout << -1 << '\n';
    } else {
        std::cout << nowx + 2 * (nowy - nowx) << '\n';
    }
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