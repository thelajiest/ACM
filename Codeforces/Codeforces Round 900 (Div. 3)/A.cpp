#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == k) {
            std::cout << "Yes\n";
            return;
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