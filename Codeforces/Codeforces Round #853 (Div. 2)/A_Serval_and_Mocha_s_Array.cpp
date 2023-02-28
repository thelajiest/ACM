#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (std::gcd(a[i], a[j]) <= 2) {
                std::cout << "Yes\n";
                return;
            }
        }
    }

    std::cout << "No\n";
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