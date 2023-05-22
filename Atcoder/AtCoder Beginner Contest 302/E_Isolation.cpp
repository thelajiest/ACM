#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> deg(N);
    std::vector<std::set<int>> adj(N);
    int ans = N;

    while (Q--) {
        int Op;
        std::cin >> Op;
        if (Op == 1) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;
            adj[u].insert(v);
            adj[v].insert(u);
            if (deg[u] == 0) ans--;
            if (deg[v] == 0) ans--;
            deg[u]++;
            deg[v]++;
        } else {
            int x;
            std::cin >> x;
            x--;
            if (deg[x] != 0) {
                ans++;
                deg[x] = 0;
            }
            for (const auto& to : adj[x]) {
                adj[to].erase(x);
                deg[to]--;
                if (deg[to] == 0) ans++;
            }
            adj[x].clear();
        }
        std::cout << ans << '\n';
    }
    return 0;
}