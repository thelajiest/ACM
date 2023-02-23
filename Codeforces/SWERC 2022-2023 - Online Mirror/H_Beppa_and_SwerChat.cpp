#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> go(n), a(n), b(n);

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        x--;
        a[i] = x;
        go[x] = i;
    }

    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
    }

    int p = n - 2;
    while (p >= 0) {
        if (go[b[p]] > go[b[p + 1]]) {
            std::cout << p + 1 << '\n';
            return;
        }
        p--;
    }

    std::cout << 0 << '\n';
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