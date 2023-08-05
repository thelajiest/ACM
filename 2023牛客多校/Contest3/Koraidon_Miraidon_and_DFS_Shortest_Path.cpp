#include <bits/stdc++.h>

using i64 = std::int64_t;

struct DominatorTree {
   public:
    std::vector<std::vector<int>> domTree;
    DominatorTree(const std::vector<std::vector<int>>& adj, int root) {
        build(adj, root);
    }

    void build(const std::vector<std::vector<int>>& adj, int root) {
        g = adj;
        rg.resize(adj.size());
        par.assign(g.size(), 0);
        idom.assign(g.size(), -1);
        semi.assign(g.size(), -1);
        ord.reserve(g.size());
        UnionFind uf(semi);

        const int N = (int)g.size();
        dfs(root);
        for (int i = 0; i < N; i++) {
            for (auto& to : g[i]) {
                if (~semi[i]) rg[to].emplace_back(i);
            }
        }

        std::vector<std::vector<int>> bucket(N);
        std::vector<int> U(N);
        for (int i = (int)ord.size() - 1; i >= 0; i--) {
            int x = ord[i];
            for (int v : rg[x]) {
                v = uf.eval(v);
                if (semi[x] > semi[v]) semi[x] = semi[v];
            }
            bucket[ord[semi[x]]].emplace_back(x);
            for (int v : bucket[par[x]]) U[v] = uf.eval(v);
            bucket[par[x]].clear();
            uf.link(par[x], x);
        }
        for (int i = 1; i < (int)ord.size(); i++) {
            int x = ord[i], u = U[x];
            idom[x] = semi[x] == semi[u] ? semi[x] : idom[u];
        }

        domTree.resize(N);
        for (int i = 1; i < (int)ord.size(); i++) {
            int x = ord[i];
            idom[x] = ord[idom[x]];
            domTree[x].push_back(idom[x]);
            domTree[idom[x]].push_back(x);
        }
        idom[root] = root;
    }

    int operator[](const int& k) const { return idom[k]; }

   private:
    std::vector<std::vector<int>> g;
    std::vector<std::vector<int>> rg;

    struct UnionFind {
        const std::vector<int>& semi;
        std::vector<int> par, m;

        explicit UnionFind(const std::vector<int>& semi)
            : semi(semi), par(semi.size()), m(semi.size()) {
            std::iota(begin(par), end(par), 0);
            std::iota(begin(m), end(m), 0);
        }

        int find(int v) {
            if (par[v] == v) return v;
            int r = find(par[v]);
            if (semi[m[v]] > semi[m[par[v]]]) m[v] = m[par[v]];
            return par[v] = r;
        }

        int eval(int v) {
            find(v);
            return m[v];
        }

        void link(int p, int c) { par[c] = p; }
    };

    std::vector<int> ord, par;
    std::vector<int> idom, semi;

    void dfs(int idx) {
        semi[idx] = (int)ord.size();
        ord.emplace_back(idx);
        for (auto& to : g[idx]) {
            if (~semi[to]) continue;
            dfs(to);
            par[to] = idx;
        }
    }
};

struct HLD {
    int n;
    int cnt;  // dfs order [0,n)
    std::vector<std::vector<int>> adj;
    std::vector<int> par, dfn, hson, siz, top, dep;
    HLD(std::vector<std::vector<int>> tr) {
        cnt = 0;
        n = tr.size();
        adj = tr;
        par.resize(n), dfn.resize(n), hson.resize(n), siz.resize(n),
            top.resize(n), dep.resize(n);
    }

    void build(int root = 0) {
        auto dfs1 = [&](auto&& self, int u, int fa) -> void {
            par[u] = fa, siz[u] = 1, hson[u] = -1;
            for (const auto& v : adj[u]) {
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
        auto dfs2 = [&](auto&& self, int u, int tp) -> void {
            dfn[u] = cnt++;
            top[u] = tp;
            if (hson[u] == -1) return;
            self(self, hson[u], tp);
            for (const auto& v : adj[u]) {
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

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        if (x == y) continue;
        adj[x].push_back(y);
    }

    std::vector<int> par(n), dis(n, -1);
    std::queue<int> Q;
    Q.push(0);
    dis[0] = 0;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto& v : adj[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                par[v] = u;
                Q.push(v);
            }
        }
    }

    DominatorTree DTree(adj, 0);
    HLD hld(DTree.domTree);
    hld.build(0);

    bool flag = true;
    for (int x = 0; x < n; x++) {
        for (const auto& y : adj[x]) {
            if (dis[y] == dis[x] + 1) continue;
            if (dis[x] == dis[y]) flag = false;
            if (dis[x] > dis[y]) {
                if (hld.lca(x, y) != y) flag = false;
            }
        }
    }

    if (flag)
        std::cout << "Yes\n";
    else
        std::cout << "No\n";

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