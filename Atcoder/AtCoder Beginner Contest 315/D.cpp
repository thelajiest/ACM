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

    int h, w;
    std::cin >> h >> w;

    std::vector<std::vector<char>> a(h, std::vector<char>(w));
    for (int i = 0; i < h; i++) {
        std::string _;
        std::cin >> _;
        a[i] = {begin(_), end(_)};
    }

    auto f = [&w](int x, int y) { return x * w + y; };

    const std::vector<std::pair<int, int>> d = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    UnionFind uf(f(h, w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (auto [dx, dy] : d) {
                if (0 <= i + dx && i + dx < h && 0 <= j + dy && j + dy < w) {
                    int x = f(i, j);
                    int y = f(i + dx, j + dy);
                    if (a[i][j] != '.' && a[i][j] == a[i + dx][j + dy]) {
                        uf.unite(x, y);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int x = f(i, j);
            if (a[i][j] != '.' && uf.size(x) == 1) {
                ans++;
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}