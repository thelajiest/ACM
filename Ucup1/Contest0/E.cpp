#include <bits/stdc++.h>

using i64 = std::int64_t;

struct HLD {
    int n;
    int cnt;  // dfs order [0,n)
    std::vector<std::vector<int>> adj;
    std::vector<int> par, dfn, hson, siz, top, dep;
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
          dep(_n){};
    HLD(std::vector<std::vector<int>> tr) {
        cnt = 0;
        n = tr.size();
        adj = tr;
        par.resize(n), dfn.resize(n), hson.resize(n), siz.resize(n),
            top.resize(n), dep.resize(n);
    }

    void addEdge(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
        return;
    }

    void build(int root = 0) {
        auto dfs1 = [&](auto &&self, int u, int fa) -> void {
            par[u] = fa, siz[u] = 1, hson[u] = -1;
            for (const auto &v : adj[u]) {
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
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
            for (const auto &v : adj[u]) {
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
};
template <class T, class Cmp = std::less<T>>
struct RMQ {
    const int n;
    const Cmp cmp;
    std::vector<std::vector<T>> a;
    RMQ(const std::vector<T> &init) : n(init.size()), cmp(Cmp()) {
        int lg = std::__lg(n);
        a.assign(lg + 1, std::vector<T>(n));
        for (int j = 0; j <= lg; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                a[j][i] =
                    (j == 0 ? init[i]
                            : std::min(a[j - 1][i],
                                       a[j - 1][i + (1 << (j - 1))], cmp));
            }
        }
    }
    T rangeMin(int l, int r) {
        if (l > r - 1) return std::numeric_limits<T>::max() / 3.0;
        int k = std::__lg(r - l);
        return std::min(a[k][l], a[k][r - (1 << k)], cmp);
    }
};
void solve() {
    int n;
    std::cin >> n;

    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    RMQ<i64> rmq(a);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    HLD hld(adj);
    hld.build();

    std::vector<std::vector<int>> d(n);
    for (int i = 0; i < n; i++) {
        d[hld.dep[i]].push_back(i);
    }

    std::vector<i64> dp(n);
    std::vector<std::vector<int>> subadj(n);

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        // std::cerr << i << std::endl;
        if (d[i].size() == 0) continue;
        std::sort(d[i].begin(), d[i].end(),
                  [&](int x, int y) { return hld.dfn[x] < hld.dfn[y]; });
        std::vector<int> use;
        for (int j = 0; j + 1 < (int)d[i].size(); j++) {
            use.push_back(d[i][j]);
            int lca = hld.lca(d[i][j], d[i][j + 1]);
            use.push_back(lca);
        }
        use.push_back(d[i].back());
        use.push_back(0);

        std::sort(use.begin(), use.end());
        use.resize(std::unique(use.begin(), use.end()) - use.begin());
        std::sort(use.begin(), use.end(),
                  [&](int x, int y) { return hld.dfn[x] < hld.dfn[y]; });

        for (int j = 0; j + 1 < (int)use.size(); j++) {
            int lca = hld.lca(use[j], use[j + 1]);
            subadj[lca].push_back(use[j + 1]);
            subadj[use[j + 1]].push_back(lca);
            // std::cerr << lca << " " << use[j + 1] << std::endl;
        }

        // std::cerr << std::endl;
        auto dfs = [&](auto &&self, int u, int fa) -> void {
            i64 sum = 0;
            int cnt = 0;
            for (const auto &v : subadj[u]) {
                if (v == fa) continue;
                cnt++;
                self(self, v, u);
                sum += dp[v];
            }
            if (cnt == 0) sum = std::numeric_limits<i64>::max() / 3.0;
            if (fa != -1)
                dp[u] = std::min(sum,
                                 rmq.rangeMin(i - hld.dep[u], i - hld.dep[fa]));
            else
                dp[u] = std::min(a[i], sum);
        };
        dfs(dfs, 0, -1);
        ans += dp[0];

        for (auto x : use) {
            subadj[x].clear();
        }
    }

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