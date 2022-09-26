#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> edge;
    for (int i = 1; i <= n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.push_back(array<int, 3>{u, v, w});
    }

    sort(edge.begin(), edge.end(), [&](auto a, auto b) { return a[2] < b[2]; });

    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) f[i] = i;
    function<int(int)> find = [&](int x) {
        if (f[x] == x)
            return x;
        else
            f[x] = find(f[x]);
        return f[x];
    };
    vector<vector<pair<int, int>>> t(n + 1);
    for (auto [u, v, w] : edge) {
        int _u = find(u);
        int _v = find(v);
        if (_u == _v) continue;
        f[_u] = _v;
        t[u].emplace_back(v, w);
        t[v].emplace_back(u, w);
    }

    vector<int> dfn(n + 1), siz(n + 1), son(n + 1), top(n + 1), dep(n + 1),
        fz(n + 1), val(n + 1);

    function<void(int, int)> dfs = [&](int u, int fa) {
        dfn[u] = ++dfn[0];
        siz[u] = 1;
        fz[u] = fa;
        dep[u] = dep[fa] + 1;
        for (auto [v, w] : t[u]) {
            if (v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    };
    function<void(int, int)> dfs2 = [&](int u, int tp) {
        top[u] = tp;
        if (son[u]) dfs2(son[u], u);
        for (auto [v, w] : t[u]) {
            if (v == fz[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, 0);
            dfs2(i, i);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}