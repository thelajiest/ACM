#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    int i1, i2, in;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x == 1) i1 = i + 1;
        if (x == 2) i2 = i + 1;
        if (x == n) in = i + 1;
    }

    if (in > std::max(i1, i2))
        std::cout << std::max(i1, i2) << " " << in << '\n';
    if (in < std::min(i1, i2))
        std::cout << std::min(i1, i2) << " " << in << '\n';
    if (std::min(i1, i2) <= in && in <= std::max(i1, i2))
        std::cout << i1 << " " << i2 << '\n';

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