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

struct Info {
    int cnt = 0;
    i64 sum = 0;
};
Info operator+(const Info &a, const Info &b) {
    return {a.cnt + b.cnt, a.sum + b.sum};
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, q;
    std::cin >> n >> k >> q;

    std::vector<std::pair<int, int>> qry(q);
    for (auto &[x, y] : qry) {
        std::cin >> x >> y;
        x--;
    }

    std::vector<int> v{0};
    for (auto [x, y] : qry) v.push_back(y);
    std::sort(begin(v), end(v));
    v.resize(std::unique(begin(v), end(v)) - v.begin());

    SegmentTree<Info> st(v.size());
    st.update(0, {n, 0});

    std::vector<int> a(n, 0);
    for (const auto &[x, y] : qry) {
        int last = a[x];
        int lastId = std::lower_bound(begin(v), end(v), last) - begin(v);
        auto [lastCnt, lastSum] = st[lastId];
        st.update(lastId, {lastCnt - 1, lastSum - last});

        int now = y;
        int nowId = std::lower_bound(begin(v), end(v), now) - begin(v);
        auto [nowCnt, nowSum] = st[nowId];
        st.update(nowId, {nowCnt + 1, nowSum + now});

        a[x] = y;

        int lo = 0, hi = v.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            auto [cnt, sum] = st.query(mid, (int)v.size());
            if (cnt < k)
                hi = mid - 1;
            else
                lo = mid;
        }
        auto [ansCnt, ansSum] = st.query(lo, (int)v.size());

        int diff = ansCnt - k;
        ansSum -= 1LL * diff * v[lo];

        std::cout << ansSum << '\n';
    }
    return 0;
}