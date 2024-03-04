#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> a(n), b(m);
    std::vector<int> cnt(k);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        if (a[i] < k) cnt[a[i]] |= 1;
    }

    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
        b[i]--;
        if (b[i] < k) cnt[b[i]] |= 2;
    }

    int pa = 0, pb = 0;
    for (int i = 0; i < k; i++) {
        if (cnt[i] == 1) pa += 1;
        if (cnt[i] == 2) pb += 1;
        if (cnt[i] == 0) {
            std::cout << "NO\n";
            return;
        }
    }
    if (pa > k / 2 || pb > k / 2) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";

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