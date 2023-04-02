#include <bits/stdc++.h>

using i64 = std::int64_t;
using i128 = __int128_t;
void solve() {
    i64 n;
    std::cin >> n;

    i64 lo = 0, hi = n;
    while (lo < hi) {
        auto mid = (lo + hi) / 2;
        if ((i128)mid * mid >= n)
            hi = mid;
        else
            lo = mid + 1;
    }

    std::cout << lo - 1 << '\n';

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