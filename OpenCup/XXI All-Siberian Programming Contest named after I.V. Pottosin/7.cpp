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
    template <typename F>
    int unite(int x, int y, const F &f) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        f(x, y);
        return true;
    }
    int size(int k) { return -data[find(k)]; }
    int same(int x, int y) { return find(x) == find(y); }
};
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> mp(n, vector<int>(n));
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mp[i][j];
        }
    }
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[i][j] == 1) uf.unite(i, j);
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == uf.find(i)) cnt += ((uf.size(i)) - 1);
    }

    cout << cnt << '\n';

    return;
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