#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> vis(n + m + 1), a(n), b(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        vis[a[x - 1]] += i + 1 - b[x - 1];
        b[x - 1] = i + 1;
        int y;
        std::cin >> y;
        a[x - 1] = y;
    }

    for (int i = 0; i < n; i++) vis[a[i]] += -b[i] + m + 1;

    i64 ans = 0;
    ans += 1LL * m * (m + 1) / 2 * (n * 2);
    for (int i = 1; i <= n + m; i++) ans -= 1LL * vis[i] * (vis[i] - 1) / 2;

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