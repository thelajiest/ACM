#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), b(q);
    std::vector<std::vector<int>> cnt(31);
    for (auto& v : a) std::cin >> v;
    for (int i = 0; i < q; i++) {
        std::cin >> b[i];
        for (int j = b[i]; j <= 30; j++) {
            if (cnt[j].size() == 0) {
                cnt[j].push_back(b[i]);
                continue;
            }
            if (cnt[j].back() > b[i]) cnt[j].push_back(b[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        int last = __builtin_ctz(a[i]);
        if (last == 0) continue;

        for (auto p : cnt[last]) {
            a[i] |= (1 << (p - 1));
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
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