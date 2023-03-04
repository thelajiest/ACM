#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::multiset<int> se;

    i64 ans = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (se.size() > 0) {
                ans += *(--se.end());
                se.erase(--se.end());
            }
        } else {
            se.insert(a[i]);
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