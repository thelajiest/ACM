#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
struct UnionFind {
    vector<int> data;
    UnionFind(int N) : data(N, -1) {}
    int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }
    int unite(int x, int y) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    int size(int k) { return -data[find(k)]; }
    int same(int x, int y) { return find(x) == find(y); }
};

void solve() {
    int n, m;
    cin >> n >> m;
    assert(n != 1);
    vector<vector<int>> adj(n), iadj(n);

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        iadj[y].push_back(x);
    }

    UnionFind uf(n);

    // iadj inverse graph [x] {y1,y2,y3,...,y_t} should get the same length

    for (int x = 0; x < n; x++) {
        if (iadj[x].size() == 0) continue;
        int to = iadj[x].back();
        for (int y : iadj[x]) uf.unite(to, y);
    }
    vector<vector<int>> nadj(n);
    vector<int> deg(n);

    for (int x = 0; x < n; x++) {
        for (int y : adj[x]) {
            nadj[uf.find(x)].push_back(uf.find(y));
            deg[uf.find(y)]++;
        }
    }

    queue<int> Q;
    vector<int> D(n), vis(n);

    for (int i = 0; i < n; i++) {
        if (uf.find(i) == i && deg[i] == 0) {
            Q.push(i);
            vis[i] = 1;
        }
    }

    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (auto v : nadj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                Q.push(v);
                vis[v] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (uf.find(i) == i && vis[i] == 0) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    vis.assign(n, 0);

    Q.push(uf.find(0));
    D[uf.find(0)] = 1;
    vis[uf.find(0)] = 1;
    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (auto v : nadj[u]) {
            D[v] = max(D[v], D[u] + 1);
            if (vis[v]) continue;
            Q.push(v);
            vis[v] = 1;
        }
    }
    vector<int> ans(n);
    for (int x = 0; x < n; x++) {
        for (int y : adj[x]) {
            ans[y] = D[uf.find(y)] - D[uf.find(x)];
        }
    }
    ans[0] = 1;
    ans[n - 1] = 1;
    for (int i = 0; i < n; i++) {
        assert(ans[i] >= 1 && ans[i] <= 1E9);
        cout << ans[i] << " \n"[i == n - 1];
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}