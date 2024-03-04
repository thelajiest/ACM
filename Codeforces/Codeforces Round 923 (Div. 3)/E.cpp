#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> r(n);
    int p = 0;

    for (int i = 0; i < k; i++) {
        std::vector<int> t;
        for (int j = i; j < n; j += k) t.push_back(++p);
        if (i & 1) std::reverse(t.begin(), t.end());
        for (int j = i, q = 0; j < n; j += k, q++) r[j] = t[q];
    }

    for (int i = 0; i < n; i++) {
        std::cout << r[i] << " \n"[i == n - 1];
    }

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