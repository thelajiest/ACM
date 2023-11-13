#include <bits/stdc++.h>
using i64 = std::int64_t;

struct UnionFind {
    std::vector<int> data;
    UnionFind(int N) : data(N, -1) {}

    int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }

    int unite(int x, int y) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int size(int k) { return -data[find(k)]; }

    int same(int x, int y) { return find(x) == find(y); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    UnionFind uf(1000);
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (uf.same(x, y)) {
            std::cout << "Y\n";
        } else {
            std::cout << "N\n";
            uf.unite(x, y);
        }
    }

    return 0;
}