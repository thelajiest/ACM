#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename Info>
struct SegmentTree {
    int N;
    int size;
    vector<Info> seg;

    SegmentTree(int _N) { init(_N); }

    //[0,v.size)
    SegmentTree(const vector<Info> &v) {
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
    int len = 0;
    int lx, rx;
    int lt = 0, rt = 0;
    int sum = 0;
    int sump = 0, sumn = 0;
};

Info operator+(const Info &a, const Info &b) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;
    if (a.rx != b.lx && a.rx != 0 && b.lx != 0) {
        Info res;
        res.len = a.len + b.len;
        res.lx = a.lx;
        res.rx = b.rx;
        res.lt = a.lt;
        res.rt = b.rt;

        if (a.lt == a.len) res.lt = a.len + b.lt;

        if (b.lt == b.len) res.rt = b.len + a.rt;

        res.sum = a.sum - a.rt / 2 + b.sum - b.lt / 2 + (a.rt + b.lt) / 2;
        if (res.lt + res.rt > res.len) {
            res.lt = res.rt = res.len;
            res.sum = res.len / 2;
        }
        res.sumn = a.sumn + b.sumn;
        res.sump = a.sump + b.sump;

        return res;
    }
    return {a.len + b.len,   a.lx,           b.rx, a.lt, b.rt, a.sum + b.sum,
            a.sump + b.sump, a.sumn + b.sumn};
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Info> init(2 * n);

    vector<vector<int>> cnt(m + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x].push_back(i);
        cnt[x].push_back(i + n);
        init[i].len = 1;
        init[i].lx = init[i].rx = 1;
        init[i].lt = init[i].rt = 1;

        init[i].sump = 1;
        init[i + n] = init[i];
    }
    SegmentTree<Info> st(init);
    for (int i = 1; i <= m; i++) {
        int l = 2 * n + 1, r = -1;
        for (auto it : cnt[i - 1]) {
            st.update(it, {1, -1, -1, 1, 1, 0, 0, -1});
        }
        for (auto it : cnt[i]) {
            st.update(it, {1, 0, 0, 0, 0, 0, 0, 0});
            l = min(l, it);
        }
        auto now = st.query(0, n);
        if (-now.sumn + now.sump == n)
            cout << "-1"
                 << " \n"[i == m];
        else
            cout << st.query(l, l + n).sum - now.sumn + now.sump
                 << " \n"[i == m];
    }
    return 0;
}