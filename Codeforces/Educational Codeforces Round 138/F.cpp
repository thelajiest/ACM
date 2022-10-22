#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <class T>
struct BIT {
    int N;
    vector<T> data;
    BIT() = default;
    BIT(int size) { init(size); }
    void init(int size) {
        N = size + 2;
        data.assign(N + 1, {});
    }
    // get sum of [0,k]
    T sum(int k) const {
        if (k < 0) return T{};  // return 0 if k < 0
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }
    // getsum of [l,r]
    inline T sum(int l, int r) const { return sum(r) - sum(l - 1); }
    // get value of k
    inline T operator[](int k) const { return sum(k) - sum(k - 1); }
    // data[k] += x
    void add(int k, T x) {
        for (++k; k < N; k += k & -k) data[k] += x;
    }
    // range add x to [l,r]
    void imos(int l, int r, T x) {
        add(l, x);
        add(r + 1, -x);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> t(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    vector<int> siz(n + 1), son(n + 1), f(n + 1), dep(n + 1);
    auto dfs1 = [&](auto self, int u, int fa) -> void {
        siz[u] = 1;
        f[u] = fa;
        dep[u] = dep[fa] + 1;
        for (auto v : t[u]) {
            if (v == fa) continue;
            self(self, v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    };
    dfs1(dfs1, 1, 0);
    vector<int> dfn(n + 1), top(n + 1);
    int cnt = 0;
    auto dfs2 = [&](auto self, int u, int tp) -> void {
        dfn[u] = cnt++;
        top[u] = tp;
        if (!son[u]) return;
        self(self, son[u], tp);
        for (auto v : t[u]) {
            if (v == f[u] || v == son[u]) continue;
            self(self, v, v);
        }
    };
    dfs2(dfs2, 1, 0);

    int m;
    cin >> m;

    vector<BIT<i64>> bit(21, BIT<i64>(cnt));
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            int step = 0;
            i64 ans = 0;
            while (step <= 20 && x) {
                ans += bit[step].sum(dfn[x]);
                x = f[x];
                step++;
            }
            cout << ans << '\n';
        }
        if (op == 2) {
            int u, v, k, d;
            cin >> u >> v >> k >> d;

            while (top[u] != top[v]) {
                if (dep[top[u]] < dep[top[v]]) swap(u, v);
                bit[d].imos(dfn[top[u]], dfn[u], k);
                u = f[top[u]];
            }
            if (dep[u] > dep[v]) swap(u, v);
            if (u != v) bit[d].imos(dfn[u] + 1, dfn[v], k);
            int step = d;
            while (step >= 0) {
                if (u == 1) {
                    for (int i = 0; i <= step; i++)
                        bit[i].imos(dfn[u], dfn[u], k);
                    break;
                }
                bit[step].imos(dfn[u], dfn[u], k);
                if (step == 0) break;
                step--;
                bit[step].imos(dfn[u], dfn[u], k);
                u = f[u];
            }
        }
    }
    return 0;
}