#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    int ans = 0;

    std::vector<int> a(n);

    for (int i = 0; i < n; i++) std::cin >> a[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                ans++;
                break;
            }
        }
    }

    std::cout << ans << '\n';

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