#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, c0;
    std::cin >> n >> c0;
    c0--;

    std::vector<std::vector<int>> adj(n);

    std::vector<int> c(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> c[i];
        c[i]--;
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> f(n);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        f[u] = fa;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };

    dfs(dfs, c0, -1);

    std::vector<int> dp(n, n + 1), vis(n, 0);
    vis[c0] = 1;

    int ans = n + 1;
    for (int i = 0; i < n - 1; i++) {
        int cur = c[i];
        vis[cur] = 1;
        int step = 0;
        ans = std::min(ans, dp[cur]);
        while (true && step < ans) {
            cur = f[cur];
            if (cur == -1) break;
            step++;
            if (vis[cur] == 1) {
                ans = std::min(ans, step);
            } else
                ans = std::min(ans, step + dp[cur]);
            dp[cur] = std::min(dp[cur], step);
        }
        std::cout << ans << ' ';
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