#include <bits/stdc++.h>

using i64 = std::int64_t;

struct Node {
    Node* l;
    Node* r;
    i64 x;
    i64 sum = 0;
    Node() : l(nullptr), r(nullptr), x(0), sum(0){};
};

Node* build(int l, int r) {
    auto nt = new Node();
    if (r - l == 1) {
        return nt;
    }

    int m = (l + r) / 2;
    nt->l = build(l, m);
    nt->r = build(m, r);

    return nt;
}

Node* add(Node* t, int l, int r, int x, i64 real) {
    Node* nt = new Node();

    if (t) {
        *nt = *t;
    }

    if (r - l == 1) {
        nt->x += 1;
        nt->sum += real;
        return nt;
    }

    int m = (l + r) / 2;

    if (x < m)
        nt->l = add(nt->l, l, m, x, real);
    else
        nt->r = add(nt->r, m, r, x, real);

    nt->x = (nt->l->x) + (nt->r->x);
    nt->sum = (nt->l->sum) + (nt->r->sum);

    return nt;
}
i64 query(Node*& q, int l, int r, int k) {
    if (r - l == 1) {
        if (q->x == 0) return 0;
        return 1LL * (q->sum) / (q->x) * k;
    }
    int cnt = (q->l->x);
    int m = (l + r) / 2;

    i64 ret = 0;
    if (k <= cnt) {
        ret += query(q->l, l, m, k);
    } else {
        ret += (q->l->sum) + query(q->r, m, r, k - cnt);
    }

    return ret;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<i64, i64>> dish(n);
    for (auto& [a, b] : dish) {
        std::cin >> a >> b;
    }

    std::sort(begin(dish), end(dish),
              [&](auto x, auto y) { return x.second < y.second; });

    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(dish[i].first);
    }
    std::sort(begin(v), end(v));
    v.resize(std::unique(begin(v), end(v)) - begin(v));
    int sz = v.size();
    std::vector<Node*> SegTree(n + 1);
    SegTree[0] = build(0, sz);

    for (int i = 0; i < n; i++) {
        int p = std::lower_bound(v.begin(), v.end(), dish[i].first) - v.begin();
        SegTree[i + 1] = add(SegTree[i], 0, sz, p, v[p]);
    }

    auto W = [&](int k, int x) -> i64 {
        auto ret = query(SegTree[x], 0, sz, k - 1);
        return ret + dish[x].first + dish[x].second;
    };

    std::vector<i64> ans(n + 1, -1);
    auto dfs = [&](auto&& self, int x1, int y1, int x2, int y2) -> void {
        if (x1 > y1) return;
        int m1 = (x1 + y1) / 2;
        int m2 = 0;

        i64 min = 1E18;
        for (int x = std::max(x2, m1 - 1); x <= y2; x++) {
            auto cur = W(m1, x);
            if (cur < min) {
                min = cur;
                m2 = x;
            }
        }
        ans[m1] = min;
        self(self, x1, m1 - 1, x2, m2);
        self(self, m1 + 1, y1, m2, y2);
    };

    dfs(dfs, 1, n, 0, n - 1);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}