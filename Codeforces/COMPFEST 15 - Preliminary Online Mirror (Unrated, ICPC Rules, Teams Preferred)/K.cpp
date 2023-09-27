#include <bits/stdc++.h>

using i64 = std::int64_t;

template <typename T, int D>
struct kthLiChaoTree {
    const T INF = std::numeric_limits<T>::max() / 3.0;
    struct line {
        T a, b;
        line() : a(0), b(-INF) {}
        line(T a, T b) : a(a), b(b) {}
        T get(T x) { return a * x + b; }
    };
    int N;
    std::vector<T> x;
    std::vector<std::vector<line>> ST;
    kthLiChaoTree() {}
    kthLiChaoTree(const std::vector<T>& x2) {
        x = x2;
        std::sort(x.begin(), x.end());
        int N2 = x.size();
        N = 1;
        while (N < N2) {
            N *= 2;
        }
        x.resize(N);
        for (int i = N2; i < N; i++) {
            x[i] = x[N2 - 1];
        }
        ST = std::vector<std::vector<line>>(N * 2 - 1);
        for (int i = 0; i < N * 2 - 1; i++) {
            ST[i].reserve(D * 2);
        }
    }
    void line_add(T a, T b) {
        line L(a, b);
        int i = 0, l = 0, r = N;
        while (true) {
            ST[i].push_back(L);
            if (ST[i].size() < D * 2) {
                break;
            }
            int m = (l + r) / 2;
            int p = 0;
            T tmp = ST[i][0].get(x[m]);
            for (int j = 1; j < D * 2; j++) {
                T tmp2 = ST[i][j].get(x[m]);
                if (tmp2 < tmp) {
                    tmp = tmp2;
                    p = j;
                }
            }
            if (i >= N - 1) {
                ST[i].erase(ST[i].begin() + p);
                break;
            }
            int cntL = 0, cntR = 0;
            T tmpL = ST[i][p].get(x[l]);
            T tmpR = ST[i][p].get(x[r - 1]);
            for (int j = 0; j < D * 2; j++) {
                if (j != p) {
                    if (tmpL <= ST[i][j].get(x[l])) {
                        cntL++;
                        if (tmpR <= ST[i][j].get(x[r - 1])) {
                            cntR++;
                        }
                    } else {
                        cntR++;
                    }
                }
            }
            L = ST[i][p];
            std::swap(ST[i][p], ST[i].back());
            ST[i].pop_back();
            if (cntL < D) {
                i = i * 2 + 1;
                r = m;
            } else if (cntR < D) {
                i = i * 2 + 2;
                l = m;
            } else {
                break;
            }
        }
    }
    std::vector<T> get_kth_max(T x2, int k) {
        int p = std::lower_bound(x.begin(), x.end(), x2) - x.begin();
        p += N - 1;
        std::vector<T> res;
        for (line L : ST[p]) {
            res.push_back(L.get(x2));
        }
        while (p > 0) {
            p = (p - 1) / 2;
            for (line L : ST[p]) {
                res.push_back(L.get(x2));
            }
        }
        std::sort(res.begin(), res.end(), std::greater<T>());
        res.resize(k, 0);
        return res;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, i64>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        u--, v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    std::vector<i64> d1(n), d2(n), dep(n);
    std::vector<std::multiset<i64>> dlist(n);
    i64 d = 0;
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        d1[u] = d2[u] = 0;
        dep[u] = dep[fa] + 1;
        for (const auto& [v, w] : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
            auto t = d1[v] + w;
            dlist[u].insert(t);
            if (t > d1[u]) {
                d2[u] = d1[u];
                d1[u] = t;
            } else if (t > d2[u])
                d2[u] = t;
        }
        d = std::max(d, d1[u] + d2[u]);
    };
    dfs(dfs, 0, 0);

    std::fill(d2.begin(), d2.end(), 0);
    auto dfs2 = [&](auto&& self, int u, int fa) -> void {
        for (const auto& [v, w] : adj[u]) {
            if (v == fa) continue;
            d2[v] = d2[u] + w;
            auto it = dlist[u].find(d1[v] + w);
            dlist[u].erase(it);
            if (dlist[u].size() != 0) {
                auto max = *std::prev(dlist[u].end());
                d2[v] = std::max(d2[v], max + w);
            }
            dlist[u].insert(d1[v] + w);
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, 0);

    int q;
    std::cin >> q;
    std::vector<std::pair<int, i64>> Q(q);
    std::vector<std::vector<i64>> cnt(n);
    for (int i = 0; i < q; i++) {
        int x;
        i64 k;
        std::cin >> x >> k;
        x--;
        Q[i] = {x, k};
        cnt[x].push_back(k);
    }

    std::vector<int> a;
    std::vector<kthLiChaoTree<i64, 2>> segTree;
    for (int x = 0; x < n; x++) {
        segTree.emplace_back(cnt[x]);
        for (const auto& [y, w] : adj[x]) {
            if (dep[y] > dep[x]) {
                segTree[x].line_add(w, d1[y]);
            } else {
                segTree[x].line_add(w, d2[x] - w);
            }
        }
    }

    for (const auto& [x, k] : Q) {
        auto dc = segTree[x].get_kth_max(k, 2);
        auto ans = std::max({d, dc[0] + dc[1]});
        std::cout << ans << '\n';
    }

    return 0;
}