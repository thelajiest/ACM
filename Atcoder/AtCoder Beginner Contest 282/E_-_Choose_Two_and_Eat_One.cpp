#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

i64 power(i64 a, i64 b, i64 mod) {
    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, m;
    cin >> n >> m;

    vector<array<i64, 3>> edge;

    vector<int> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            edge.push_back(array<i64, 3>{
                i, j, (power(a[i], a[j], m) + power(a[j], a[i], m)) % m});
        }
    }

    sort(edge.begin(), edge.end(),
         [&](auto a, auto b) -> bool { return a[2] > b[2]; });
    UnionFind uf(n);
    i64 ans = 0;
    int cnt = 0;
    for (auto [u, v, val] : edge) {
        if (uf.same(u, v)) continue;
        cnt++;
        uf.unite(u, v);
        ans += val;
        if (cnt == n - 1) break;
    }
    cout << ans;
    return 0;
}