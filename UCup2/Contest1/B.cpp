#include <bits/stdc++.h>

using i64 = std::int64_t;
struct HLD {
    int n;
    int cnt;  // dfs order [0,n)
    std::vector<std::vector<std::pair<int, i64>>> adj;
    std::vector<int> par, dfn, hson, siz, top, dep, d;
    HLD() = delete;
    HLD(int _n)
        : n(_n),
          cnt(0),
          adj(_n),
          par(_n),
          dfn(_n),
          hson(_n),
          siz(_n),
          top(_n),
          dep(_n),
          d(_n){};
    HLD(std::vector<std::vector<std::pair<int, i64>>> tr) {
        cnt = 0;
        n = tr.size();
        adj = tr;
        par.resize(n), dfn.resize(n), hson.resize(n), siz.resize(n),
            top.resize(n), dep.resize(n), d.resize(n);
    }

    void build(int root = 0) {
        auto dfs1 = [&](auto &&self, int u, int fa) -> void {
            par[u] = fa, siz[u] = 1, hson[u] = -1;
            for (const auto &[v, w] : adj[u]) {
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                d[v] = d[u] + w;
                self(self, v, u);
                siz[u] += siz[v];
                if (hson[u] == -1)
                    hson[u] = v;
                else if (siz[hson[u]] < siz[v])
                    hson[u] = v;
            }
        };
        dfs1(dfs1, root, -1);
        auto dfs2 = [&](auto &&self, int u, int tp) -> void {
            dfn[u] = cnt++;
            top[u] = tp;
            if (hson[u] == -1) return;
            self(self, hson[u], tp);
            for (const auto &[v, w] : adj[u]) {
                if (v == par[u] || v == hson[u]) continue;
                self(self, v, v);
            }
        };
        dfs2(dfs2, root, root);
        return;
    }

    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]])
                u = par[top[u]];
            else
                v = par[top[v]];
        }
        return ((dep[u] > dep[v]) ? v : u);
    }

    int lca(const std::vector<int> &node) {
        int t = node[0];
        for (int i = 1; i < (int)node.size(); i++) t = lca(t, node[i]);
        return t;
    }
};
void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<std::pair<int, i64>>> adj(n);
    std::vector<int> red(n);
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        x--;
        red[x] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        i64 w;
        std::cin >> x >> y;
        std::cin >> w;
        x--, y--;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }

    std::vector<i64> dis(n), d(n);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        for (const auto &[v, w] : adj[u]) {
            if (v == fa) continue;
            if (red[v])
                dis[v] = 0;
            else
                dis[v] = dis[u] + w;
            d[v] = d[u] + w;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, -1);
    HLD hld(adj);
    hld.build(0);
    while (q--) {
        int k;
        std::cin >> k;
        std::vector<int> qNode(k);
        for (int i = 0; i < k; i++) {
            std::cin >> qNode[i];
            qNode[i]--;
        }

        std::sort(begin(qNode), end(qNode),
                  [&](auto &a, auto &b) { return dis[a] > dis[b]; });
        int prefixLCA = qNode[0];
        i64 prefixMax = 0;

        i64 ans = dis[qNode[0]];
        for (int i = 0; i < k; i++) {
            int node = qNode[i];
            prefixLCA = hld.lca(prefixLCA, node);
            prefixMax = std::max<i64>(prefixMax, d[node]);
            if (i < k - 1)
                ans = std::min(
                    ans, std::max(prefixMax - d[prefixLCA], dis[qNode[i + 1]]));
            else
                ans = std::min(ans, prefixMax - d[prefixLCA]);
        }
        std::cout << ans << '\n';
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