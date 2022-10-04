#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
template <class T>
struct HLD {
    int n;
    vector<vector<pair<int, T>>> t;
    vector<T> dis;
    vector<int> siz, son, top, dep, fa;
    HLD(int _n, int _m)
        : t(_n + 1),
          dis(_n + 1),
          siz(_n + 1),
          son(_n + 1),
          top(_n + 1),
          fa(_n + 1),
          dep(_n + 1),
          n(_n) {
        for (int i = 1; i <= _m; i++) {
            int u, v;
            T w;
            cin >> u >> v >> w;
            t[u].emplace_back(v, w);
            t[v].emplace_back(u, w);
        }
    };
    HLD(const vector<vector<pair<int, T>>>& g, int _n)
        : t(g),
          dis(_n + 1),
          siz(_n + 1),
          son(_n + 1),
          top(_n + 1),
          fa(_n + 1),
          dep(_n + 1),
          n(_n) {}

    void Decomposition(int root) {
        function<void(int, int)> dfs1 = [&](int u, int f) {
            fa[u] = f;
            dep[u] = dep[f] + 1;
            siz[u] = 1;
            for (auto [v, w] : t[u]) {
                if (v == f) continue;
                dis[v] = dis[u] + w;
                dfs1(v, u);
                siz[u] += siz[v];
                if (siz[v] > siz[son[u]]) {
                    son[u] = v;
                }
            }
        };
        dfs1(root, 0);
        function<void(int, int)> dfs2 = [&](int u, int f) {
            top[u] = f;
            if (son[u] == 0) return;
            dfs2(son[u], f);
            for (auto [v, w] : t[u]) {
                if (v == fa[u] || v == son[u]) continue;
                dfs2(v, v);
            }
        };
        dfs2(root, root);
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int find(int u, int f) {
        int res = 0;
        while (top[u] != top[f]) {
            res = top[u];
            u = fa[top[u]];
        }
        return u == f ? res : son[f];
    }
};
template <class T>
struct BCT {
    int n;
    vector<vector<pair<int, T>>> cactus, adj;
    vector<int> dfn, low, fa;
    vector<T> b, sum;
    int cnt = 0, ext;
    BCT(int _n, int _m)
        : cactus(_n + 1),
          adj(2 * _n + 1),
          dfn(_n + 1),
          low(_n + 1),
          fa(_n + 1),
          b(_n + 1),
          sum(2 * _n + 1),
          n(_n),
          ext(_n) {
        for (int i = 1; i <= _m; i++) {
            int u, v;
            cin >> u >> v;
            T w;
            cin >> w;
            cactus[u].emplace_back(v, w);
            cactus[v].emplace_back(u, w);
        }
    };
    void build() {
        function<void(int, int)> tarjan = [&](int u, int f) {
            dfn[u] = low[u] = ++cnt;
            for (auto [v, w] : cactus[u]) {
                if (v == f) continue;
                if (!dfn[v]) {
                    fa[v] = u, b[v] = w;
                    tarjan(v, u);
                    low[u] = min(low[u], low[v]);
                } else
                    low[u] = min(low[u], dfn[v]);
                if (low[v] <= dfn[u]) continue;
                adj[u].emplace_back(v, w);
                adj[v].emplace_back(u, w);
            }
            for (auto [v, w] : cactus[u]) {
                if (fa[v] == u || dfn[v] <= dfn[u]) continue;
                auto solve = [&](int u, int v, T w) {
                    ext++;
                    int pw, i = v;
                    T pre = w;
                    while (i != fa[u]) {
                        sum[i] = pre;
                        pre += b[i];
                        i = fa[i];
                    }
                    sum[ext] = sum[u];
                    sum[u] = 0;
                    i = v;
                    while (i != fa[u]) {
                        pw = min(sum[i], sum[ext] - sum[i]);
                        adj[ext].emplace_back(i, pw);
                        adj[i].emplace_back(ext, pw);
                        i = fa[i];
                    }
                };
                solve(u, v, w);
            }
        };
        tarjan(1, 0);
    }
};
template <class T>
T CactusQuery(HLD<T>& hld, const BCT<T>& bct, int u, int v) {
    T ans = 0;
    int p = hld.lca(u, v);
    if (p <= bct.n) {
        ans = hld.dis[u] + hld.dis[v] - (hld.dis[p] * 2);
    } else {
        int A = hld.find(u, p), B = hld.find(v, p);
        ans = hld.dis[u] + hld.dis[v] - hld.dis[A] - hld.dis[B];
        if (bct.sum[A] < bct.sum[B]) swap(A, B);
        ans +=
            min(bct.sum[A] - bct.sum[B], bct.sum[p] + bct.sum[B] - bct.sum[A]);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int q;
    cin >> q;

    BCT<i64> bct(n, m);
    bct.build();
    HLD<i64> hld(bct.adj, bct.ext);
    hld.Decomposition(1);
    while (q--) {
        int u, v;
        cin >> u >> v;

        cout << CactusQuery<i64>(hld, bct, u, v) << '\n';
    }

    return 0;
}