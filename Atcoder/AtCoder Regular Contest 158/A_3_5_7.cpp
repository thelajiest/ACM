#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    i64 a, b, c;
    std::cin >> a >> b >> c;

    if ((a + b + c) % 3 != 0) {
        std::cout << "-1\n";
        return;
    }

    i64 d = (a + b + c) / 3;
    std::vector<i64> p{a % 2, b % 2, c % 2, d % 2};
    for (int i = 0; i < 4; i++)
        if (p[i] != p[0]) {
            std::cout << "-1\n";
            return;
        }

    std::cout << (std::max<i64>(a - d, 0LL) + std::max<i64>(b - d, 0LL) +
                  std::max<i64>(c - d, 0LL)) /
                     2
              << "\n";
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