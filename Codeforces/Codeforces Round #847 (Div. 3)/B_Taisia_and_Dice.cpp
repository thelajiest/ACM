#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, s, r;
    std::cin >> n >> s >> r;

    std::vector<int> ans(n, s - r);
    int res = n * (s - r) - s;
    for (int i = 0; i < n; i++) {
        auto now = std::min(ans[i] - 1, res);
        ans[i] -= now;
        res -= now;
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
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