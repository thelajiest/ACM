#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x;
    int n;
    cin >> n;
    vector<vector<int>> t(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        t[x].push_back(y);
        t[y].push_back(x);
    }
    vector<array<int, 26>> fa(n + 1);
    vector<int> dep(n + 1);
    function<void(int, int)> dfs = [&](int root, int fno) {
        fa[root][0] = fno;
        dep[root] = dep[fa[root][0]] + 1;

        for (int i = 1; i <= 25; ++i) {
            fa[root][i] = fa[fa[root][i - 1]][i - 1];
        }
        for (auto v : t[root]) {
            if (v == fno) continue;
            dfs(v, root);
        }
    };

    dfs(1, 0);

    auto get = [&](int u, int k) {
        if (k == 0) return u;
        for (int i = 25; i >= 0; i--) {
            if ((k >> i) & 1) u = fa[u][i];
        }
        return u;
    };
    vector<int> diff(n + 1);

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        int u = i, v = get(i, x);
        diff[u]++, diff[fa[v][0]]--;
    }
    function<void(int, int)> dfs2 = [&](int u, int fa) {
        for (auto v : t[u]) {
            if (v == fa) continue;
            dfs2(v, u);
            diff[u] += diff[v];
        }
    };
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << diff[i] << " ";
}