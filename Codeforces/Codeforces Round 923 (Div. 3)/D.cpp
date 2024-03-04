#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::vector<int> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (i != 0) d[i] = a[i] - a[i - 1];
    }

    for (int i = 1; i < n; i++) {
        if (d[i] != 0) d[i] = 1;
    }

    std::vector<int> next(n, n + 1);
    int p = n + 1;
    for (int i = n - 1; i > 0; i--) {
        if (d[i] == 1) {
            p = i;
            next[i] = p;
        } else {
            next[i] = p;
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        r--;
        int pos = next[l];
        if (pos > r)
            std::cout << "-1 -1\n";
        else {
            std::cout << pos << " " << pos + 1 << '\n';
            assert(a[pos - 1] != a[pos]);
        }
    }

    std::cout << '\n';

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