#include <bits/stdc++.h>

using i64 = std::int64_t;

template <class G>
struct BlockCutTree {
    G tree;
    std::vector<int> dfn, low;
    std::vector<int> ar;  // cut vertex 1/0
    std::vector<int> idar, idcc;

    std::vector<std::vector<int>> bcc;
    std::vector<std::vector<int>> aux;  // block cut tree
    BlockCutTree(const G& tree) : tree(tree) {
        int sz = tree.size();
        dfn.assign(sz, -1);
        low.assign(sz, -1);
        ar.assign(sz, 0);
        idar.assign(sz, -1);
        idcc.assign(sz, -1);

        build();
    }
    void build() {
        int cnt = 0;
        std::stack<int> st;
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            dfn[u] = low[u] = cnt++;
            int childCnt = 0;
            st.push(u);
            for (const auto& v : tree[u]) {
                if (v == fa) continue;
                if (dfn[v] == -1) {
                    childCnt++;
                    self(self, v, u);
                    low[u] = std::min(low[u], low[v]);
                    if (low[v] >= dfn[u]) {
                        ar[u] = 1;
                        std::vector<int> curBcc;
                        while (true) {
                            int cur = st.top();
                            curBcc.push_back(cur);
                            st.pop();
                            if (cur == v) break;
                        }
                        curBcc.push_back(u);
                        bcc.push_back(curBcc);
                    }
                } else
                    low[u] = std::min(low[u], dfn[v]);
            }
            if (fa < 0 && childCnt < 2) ar[u] = 0;
        };
        for (int i = 0; i < (int)tree.size(); i++) {
            if (dfn[i] == -1) dfs(dfs, i, -1);
        }

        std::vector<int> arSet;
        for (int i = 0; i < (int)ar.size(); i++)
            if (ar[i]) arSet.push_back(i);

        for (int i = 0; i < (int)arSet.size(); i++) idar[arSet[i]] = i;

        aux.resize(arSet.size() + bcc.size());
        std::vector<int> last(tree.size(), -1);

        for (int i = 0; i < (int)bcc.size(); i++) {
            auto add = [&](int i, int j) {
                if (i == -1 or j == -1) return;
                aux[i].push_back(j);
                aux[j].push_back(i);
                return;
            };
            for (const auto& u : bcc[i]) {
                if (idar[u] == -1)
                    idcc[u] = i + (int)arSet.size();
                else if (last[u] != i) {
                    add(i + (int)arSet.size(), idar[u]);
                    last[u] = i;
                }
            }
        }
    }
    std::vector<int>& operator[](int i) { return aux[i]; }
    int size() const { return aux.size(); }
    int id(int i) { return idar[i] == -1 ? idcc[i] : idar[i]; }
    bool is_arti(int i) { return idar[i] != -1; }
};

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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int a, b, c;
    std::cin >> a >> b >> c;
    a--, b--, c--;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    BlockCutTree BCT(adj);

    ;

    int ida = BCT.id(a);
    int idb = BCT.id(b);
    int idc = BCT.id(c);
    HLD hld(BCT.aux);
    hld.build(idb);

    int lca = hld.lca(ida, idc);
    if (lca == idb)
        std::cout << "Yes" << std::endl;
    else {
        if (BCT.is_arti(b) && hld.par[lca] == idb)
            std::cout << "Yes" << std::endl;
        else
            std::cout << "No" << std::endl;
    }

    return 0;
}