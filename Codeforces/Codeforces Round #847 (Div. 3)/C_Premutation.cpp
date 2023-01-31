#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);

    for (int i = 0; i < n; i++) {
        std::vector<int> cur(n - 1);
        for (auto& it : cur) {
            std::cin >> it;
            it--;
        }
        for (int i = 0; i < n - 2; i++) {
            adj[cur[i]].push_back(cur[i + 1]);
            deg[cur[i + 1]]++;
        }
    }

    std::queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) Q.push(i);
    }

    std::vector<int> ans;
    while (!Q.empty()) {
        auto u = Q.front();
        ans.push_back(u);
        Q.pop();
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) Q.push(v);
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] + 1 << " \n"[i == n - 1];
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