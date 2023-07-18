#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, k, x;

    std::cin >> n >> k >> x;
    std::vector<int> num;

    for (int i = 1; i <= k; i++) {
        if (i != x) num.push_back(i);
    }
    num.resize(std::min((int)num.size(), 2));

    if (num.size() == 0) {
        std::cout << "NO\n";
        return;
    }

    if (num.size() == 1) {
        int p = num.back();
        if (n % p == 0) {
            std::cout << "YES\n";
            std::cout << n / p << '\n';
            for (int i = 0; i < n / p; i++) {
                std::cout << p << " ";
            }
            std::cout << '\n';
        } else {
            std::cout << "NO\n";
        }
    } else {
        int x = num[0], y = num[1];
        for (int i = 0; i * x <= n; i++) {
            for (int j = 0; i * x + j * y <= n; j++) {
                if (i * x + j * y == n) {
                    std::cout << "YES\n";
                    std::cout << i + j << '\n';
                    for (int t1 = 0; t1 < i; t1++) {
                        std::cout << x << " ";
                    }
                    for (int t2 = 0; t2 < j; t2++) {
                        std::cout << y << " ";
                    }
                    std::cout << '\n';
                    return;
                }
            }
        }
        std::cout << "NO\n";
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