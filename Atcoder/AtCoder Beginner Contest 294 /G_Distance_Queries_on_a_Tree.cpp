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

    std::vector<std::pair<int, int>> pathP2P(int u, int v) const {
        // op length O(logn)
        std::vector<std::pair<int, int>> op;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            op.emplace_back(dfn[top[u]], dfn[u]);
            u = par[top[u]];
        }
        if (dep[u] > dep[v]) std::swap(u, v);
        op.emplace_back(dfn[u], dfn[v]);
        return (op);
    }
    template <class F>
    void processP2P(int u, int v, F f) {
        // F: void(int L, int R) refers to the process of internal [L,R]
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            f(dfn[top[u]], dfn[u]);
            u = par[top[u]];
        }
        if (dep[u] > dep[v]) std::swap(u, v);
        f(dfn[u], dfn[v]);
    }
};

template <typename Info>
struct SegmentTree {
    int N;
    int size;
    std::vector<Info> seg;

    SegmentTree(int _N) { init(_N); }

    //[0,v.size)
    SegmentTree(const std::vector<Info> &v) {
        init(v.size());
        for (int i = 0; i < (int)v.size(); i++) {
            seg[i + size] = v[i];
        }
        build();
    }
    void init(int _N) {
        N = _N;
        size = 1;
        while (size < N) size <<= 1;
        seg.assign(2 * size, Info());
    }
    void set(int k, const Info &x) { seg[k + size] = x; }
    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void update(int k, const Info &x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void add(int k, const Info &x) {
        k += size;
        seg[k] += x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    // query to [a, b)
    Info query(int a, int b) {
        Info L = Info(), R = Info();
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = L + seg[a++];
            if (b & 1) R = seg[--b] + R;
        }
        return L + R;
    }
    Info &operator[](const int &k) { return seg[k + size]; }
};

struct Info {
    i64 x = 0;
    Info &operator+=(const Info &a) {
        x += a.x;
        return *this;
    }
};
Info operator+(const Info &a, const Info &b) { return {a.x + b.x}; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::tuple<int, int, i64>> E(n - 1);
    std::vector<std::vector<int>> adj(n);
    std::vector<int> dep(n);
    std::vector<i64> val(n);
    for (auto &&[u, v, w] : E) {
        std::cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        for (auto v : adj[u]) {
            if (v != fa) self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);

    std::vector<int> id(n);
    int pcnt = 0;
    for (auto [u, v, w] : E) {
        assert(dep[u] != dep[v]);
        if (dep[u] > dep[v]) {
            val[u] = w;
            id[++pcnt] = u;
        } else {
            val[v] = w;
            id[++pcnt] = v;
        }
    }

    HLD hld(adj);
    hld.build();
    std::vector<Info> _init(n);
    for (int i = 0; i < n; i++) {
        _init[hld.dfn[i]].x = val[i];
    }
    SegmentTree<Info> ST(_init);

    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int i;
            i64 x;
            std::cin >> i >> x;
            ST.update(hld.dfn[id[i]], {x});
        } else {
            int u, v;
            std::cin >> u >> v;
            u--, v--;

            i64 sum = 0;
            auto processSum = [&](int L, int R) -> void {
                sum += ST.query(L, R + 1).x;
            };
            hld.processP2P(u, v, processSum);
            auto lca = hld.lca(u, v);
            std::cout << sum - ST.query(hld.dfn[lca], hld.dfn[lca] + 1).x
                      << '\n';
        }
    }

    return 0;
}