#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <int mod>
struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    mint &operator+=(const mint &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator-=(const mint &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator*=(const mint &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }
    mint &operator/=(const mint &p) {
        *this *= p.inverse();
        return *this;
    }
    mint operator-() const { return mint(-x); }
    mint operator+(const mint &p) const { return mint(*this) += p; }
    mint operator-(const mint &p) const { return mint(*this) -= p; }
    mint operator*(const mint &p) const { return mint(*this) *= p; }
    mint operator/(const mint &p) const { return mint(*this) /= p; }
    bool operator==(const mint &p) const { return x == p.x; }
    bool operator!=(const mint &p) const { return x != p.x; }
    mint inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
    friend istream &operator>>(istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};

template <class Info, class Tag>
struct LazySegmentTree {
    const int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << __lg(n)), tag(4 << __lg(n)) {}
    LazySegmentTree(vector<Info> init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) +
               rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};
constexpr int mod = 998244353;
using Z = mint<mod>;
using Mat = array<array<int, 4>, 4>;
struct Tag {
    int x;
    void apply(const Tag &a) { x = a.x + x; }
};

struct Info {
    Mat mat;
    int lx = -1, rx = -1;
    void apply(const Tag &a) {
        Mat res;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                res[(i + a.x) % 4][(j + a.x) % 4] = mat[i][j];
            }
        mat = res;
        lx = (lx + a.x) % 4;
        rx = (rx + a.x) % 4;
    }
};

Info operator+(const Info &a, const Info &b) {
    if (a.lx == -1 && a.rx == -1) return b;
    if (b.lx == -1 && b.rx == -1) return a;
    Mat res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            res[i][j] = a.mat[i][j] + b.mat[i][j];
        }
    res[a.rx][b.lx]++;
    return {res, a.lx, b.rx};
};
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    constexpr int N = 2E5;

    vector<Z> fac(N), invf(N);

    fac[0] = Z(1);
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * Z(i);
    invf[N - 1] = fac[N - 1].inverse();
    for (int i = N - 2; i >= 0; i--) invf[i] = invf[i + 1] * Z(i + 1);

    auto Comb = [&](int n, int m) -> Z {
        assert(n < N && m < N);
        if (n < m || m < 0 || n < 0) return Z(0);
        return fac[n] * invf[m] * invf[n - m];
    };

    string s;
    cin >> s;

    vector<Info> init(n);

    for (int i = 0; i < n; i++) {
        int now = s[i] - 'A';
        init[i] = {Mat(), now, now};
    }

    LazySegmentTree<Info, Tag> ST(init);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            ST.rangeApply(l, r, Tag{1});
        }
        if (op == 2) {
            int l, r, k;
            cin >> l >> r >> k;
            int qry = 0;
            auto rg = ST.rangeQuery(l - 1, r);

            for (int i = 0; i < 4; i++)
                for (int j = 0; j <= i; j++) qry += rg.mat[i][j];
            cout << Comb(r - l - qry, k - qry - 1) << '\n';
        }
    }

    return 0;
}
