#include <bits/stdc++.h>
using i64 = std::int64_t;

template <typename G>
struct LowLink {
    const G &g;
    int N;
    std::vector<int> ord, low, articulation;
    std::vector<std::pair<int, int>> bridge;

    LowLink(const G &_g) : g(_g), N(g.size()), ord(N, -1), low(N, -1) {
        for (int i = 0, k = 0; i < N; i++) {
            if (ord[i] == -1) k = dfs(i, k, -1);
        }
    }

    int dfs(int idx, int k, int par) {
        low[idx] = (ord[idx] = k++);
        int cnt = 0;
        bool arti = false, second = false;
        for (auto &[to, w] : g[idx]) {
            if (ord[to] == -1) {
                cnt++;
                k = dfs(to, k, idx);
                low[idx] = std::min(low[idx], low[to]);
                arti |= (par != -1) && (low[to] >= ord[idx]);
                if (ord[idx] < low[to]) {
                    bridge.emplace_back(std::minmax(idx, (int)to));
                }
            } else if (to != par || second) {
                low[idx] = std::min(low[idx], ord[to]);
            } else {
                second = true;
            }
        }
        arti |= par == -1 && cnt > 1;
        if (arti) articulation.push_back(idx);
        return k;
    }
};

template <typename G>
struct TwoEdgeConnectedComponents {
    const G &g;
    LowLink<G> low;
    std::vector<int> comp;
    int k;
    std::vector<std::vector<int>> groups, tree;
    TwoEdgeConnectedComponents(const G &g_)
        : g(g_), low(g_), comp(g_.size(), -1), k(0) {
        for (int i = 0; i < (int)g.size(); i++) {
            if (comp[i] == -1) dfs(i, -1);
        }
        groups.resize(k);
        tree.resize(k);
        for (int i = 0; i < (int)g.size(); i++) {
            groups[comp[i]].push_back(i);
        }
        for (auto &e : low.bridge) {
            int u = comp[e.first], v = comp[e.second];
            tree[u].push_back(v);
        }
    };

    int operator[](const int &k) const { return comp[k]; }

    void dfs(int i, int p) {
        if (p >= 0 && low.ord[p] >= low.low[i])
            comp[i] = comp[p];
        else
            comp[i] = k++;
        for (auto &[d, w] : g[i]) {
            if (comp[d] == -1) dfs(d, i);
        }
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        x--, y--;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    TwoEdgeConnectedComponents ecc(adj);

    std::vector<std::tuple<int, int, int>> E;
    for (int x = 0; x < n; x++) {
        for (auto [y, w] : adj[x]) {
            if (ecc[x] != ecc[y]) continue;
            if (x < y) {
                E.emplace_back(w, x, y);
            }
        }
    }

    std::sort(std::begin(E), std::end(E));

    auto [W, X, Y] = *std::begin(E);

    std::vector<int> vis(n), prev(n, -1);
    std::queue<int> Q;

    Q.push(X);
    vis[X] = 1;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto [v, w] : adj[u]) {
            if (std::minmax(u, v) == std::minmax(X, Y)) continue;
            if (vis[v]) continue;
            vis[v] = 1;
            prev[v] = u;
            Q.push(v);
        }
    }

    int p = Y;
    std::vector<int> r;
    while (p != -1) {
        r.emplace_back(p);
        p = prev[p];
    }

    std::cout << W << " " << (int)r.size() << '\n';
    for (int i = 0; i < (int)r.size(); i++) {
        std::cout << r[i] + 1 << " \n"[i == (int)r.size() - 1];
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