#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;

tuple<int, int, int> TreeDiameter(const vector<vector<int>>& t, int s = 1) {
    vector<int> f(t.size(), -1);
    vector<int> dep(t.size());
    auto dfs = [&](auto self, int u) -> void {
        for (auto v : t[u])
            if (v != f[u]) dep[v] = dep[f[v] = u] + 1, self(self, v);
    };
    dfs(dfs, s);
    int u = max_element(begin(dep) + s, end(dep)) - dep.begin();
    fill(begin(dep) + s, end(dep), 0);
    fill(begin(f) + s, end(f), -1);
    dfs(dfs, u);
    int v = max_element(begin(dep) + s, end(dep)) - dep.begin();

    vector<int> r(1, v);
    while (v != u) r.push_back(v = f[v]);

    return {r.size(), *r.begin(), *r.rbegin()};
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> t(n + 1);

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        t[x].push_back(y);
        t[y].push_back(x);
    }

    auto [D, s1, s2] = TreeDiameter(t, 1);

    int q;
    cin >> q;
    vector<pair<int, int>> Qry(q);
    for (auto&& [u, k] : Qry) cin >> u >> k;
    vector<int> ans(q, -1);

    auto solve = [&](int s) -> void {
        constexpr int Lg = 26;
        vector<array<int, Lg + 1>> fa(n + 1);
        vector<int> dep(n + 1);
        function<void(int, int)> dfs = [&](int root, int fno) {
            fa[root][0] = fno;
            dep[root] = dep[fno] + 1;

            for (int i = 1; i <= Lg; ++i) {
                fa[root][i] = fa[fa[root][i - 1]][i - 1];
            }
            for (auto v : t[root]) {
                if (v == fno) continue;
                dfs(v, root);
            }
        };

        dfs(s, 0);

        auto get = [&](int u, int k) {
            if (k >= dep[u]) return -1;
            if (k == 0) return u;
            for (int i = 25; i >= 0; i--) {
                if ((k >> i) & 1) u = fa[u][i];
            }
            return u;
        };

        for (int i = 0; i < q; i++) {
            auto [u, k] = Qry[i];
            if (ans[i] != -1) continue;
            ans[i] = get(u, k);
        }
    };
    solve(s1);
    solve(s2);
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';

    return 0;
}