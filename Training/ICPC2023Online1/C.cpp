#include <bits/stdc++.h>

using i64 = std::int64_t;

template <typename Info>
struct SegmentTree {
    int N;
    int size;
    std::vector<Info> seg;

    SegmentTree(int _N) { init(_N); }

    //[0,v.size)
    SegmentTree(const std::vector<Info> &v) {
        init(v.size());
        for (int i = 0; i < (int)v.size(); i++) {
            seg[i + size] = v[i];
        }
        build();
    }
    void init(int _N) {
        N = _N;
        size = 1;
        while (size < N) size <<= 1;
        seg.assign(2 * size, Info());
    }
    void set(int k, const Info &x) { seg[k + size] = x; }
    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void update(int k, const Info &x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void add(int k, const Info &x) {
        k += size;
        seg[k] += x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    // query to [a, b)
    Info query(int a, int b) {
        Info L = Info(), R = Info();
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = L + seg[a++];
            if (b & 1) R = seg[--b] + R;
        }
        return L + R;
    }
    Info &operator[](const int &k) { return seg[k + size]; }
};

constexpr int INF = 1E9;
struct Info {
    int x = INF;
};
Info operator+(const Info &a, const Info &b) { return {std::min(a.x, b.x)}; }

struct Info2 {
    int x = -1;
};
Info2 operator+(const Info2 &a, const Info2 &b) { return {std::max(a.x, b.x)}; }
void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }

    std::vector<std::pair<int, int>> pos(n);
    SegmentTree<Info> seg1(k);
    for (int i = 0; i < n; i++) {
        auto now = seg1.query(a[i], a[i] + 1).x;
        now = std::min(now, i);
        seg1.update(a[i], {now});
        auto left = seg1.query(a[i], k).x;
        pos[i].first = left;
    }

    SegmentTree<Info2> seg2(k);
    for (int i = n - 1; i >= 0; i--) {
        auto now = seg2.query(a[i], a[i] + 1).x;
        now = std::max(now, i);
        seg2.update(a[i], {now});
        auto right = seg2.query(a[i], k).x;
        pos[i].second = right;
    }

    std::vector<int> ans(k, 0);
    for (int i = 0; i < n; i++) {
        auto [l, r] = pos[i];
        ans[a[i]] = std::max(ans[a[i]], r - l + 1);
    }
    for (int i = 0; i < k; i++) {
        std::cout << ans[i] * 2 << " \n"[i == k - 1];
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}