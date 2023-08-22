#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        int c;
        std::cin >> c;
        for (int j = 0; j < c; j++) {
            int x;
            std::cin >> x;
            x--;
            adj[i].push_back(x);
            deg[x]++;
        }
    }

    std::vector<int> vis(n, 0);
    auto dfs = [&](auto&& self, int u) -> void {
        vis[u] = 1;
        for (const auto& v : adj[u]) {
            if (!vis[v]) self(self, v);
        }
    };

    dfs(dfs, 0);

    std::queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) Q.push(i);
    }

    std::vector<int> tp;
    tp.reserve(n);
    while (!Q.empty()) {
        auto u = Q.front();
        tp.push_back(u);
        Q.pop();

        for (const auto& v : adj[u]) {
            deg[v]--;
            if (!deg[v]) {
                Q.push(v);
            }
        }
    }

    std::reverse(begin(tp), end(tp));
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (vis[tp[i]] && tp[i]) ans.push_back(tp[i]);
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        std::cout << ans[i] + 1 << " \n"[i == (int)ans.size() - 1];
    }

    return 0;
}