#include <bits/stdc++.h>
using i64 = std::int64_t;

struct RollbackUnionFind {
    std::vector<int> data;
    std::stack<std::pair<int, int>> history;
    int inner_snap;

    RollbackUnionFind(int sz) : inner_snap(0) { data.assign(sz, -1); }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int find(int k) {
        if (data[k] < 0) return k;
        return find(data[k]);
    }

    int same(int x, int y) { return find(x) == find(y); }

    int size(int k) { return (-data[find(k)]); }

    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }

    void snapshot() { inner_snap = int(history.size() >> 1); }

    int get_state() { return int(history.size() >> 1); }

    void rollback(int state = -1) {
        if (state == -1) state = inner_snap;
        state <<= 1;
        assert(state <= (int)history.size());
        while (state < (int)history.size()) undo();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    i64 K;
    std::cin >> n >> m >> K;

    std::vector<std::tuple<int, int, i64>> E(m);
    for (auto& [u, v, w] : E) {
        std::cin >> u >> v >> w;
        u--, v--;
    }

    i64 ans = std::numeric_limits<i64>::max(), sum = 0;
    RollbackUnionFind uf(n);

    auto dfs = [&](auto&& self, int id, int left) -> void {
        const auto& [u, v, w] = E[id];
        sum += w;
        uf.unite(u, v);

        if (left == 0) {
            if (uf.size(0) == n) {
                ans = std::min(ans, sum % K);
            }
            uf.undo();
            sum -= w;
            return;
        }

        for (int k = id + 1; k < m; k++) {
            self(self, k, left - 1);
        }
        uf.undo();
        sum -= w;

        return;
    };

    for (int i = 0; i < m; i++) {
        dfs(dfs, i, n - 2);
    }

    std::cout << ans << std::endl;

    return 0;
}