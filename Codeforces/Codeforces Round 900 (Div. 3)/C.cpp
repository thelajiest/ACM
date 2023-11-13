#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    i64 n, k, x;

    std::cin >> n >> k >> x;

    i64 lo = k * (k + 1) / 2;
    i64 hi = n * (n + 1) / 2 - (n - k) * (n - k + 1) / 2;
    if (lo <= x && x <= hi) {
        std::cout << "YES\n";
    } else
        std::cout << "NO\n";
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