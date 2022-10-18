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

constexpr int mod = 998244353;
constexpr int N = 3E5;
using Z = mint<mod>;
using Mat = array<array<Z, 2>, 2>;

struct Info {
    Mat x = {array<Z, 2>{1, 0}, array<Z, 2>{0, 1}};
};
Info operator+(const Info &a, const Info &b) {
    Mat mul = Mat();
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) mul[i][j] += a.x[i][k] * b.x[k][j];
    return {mul};
}

const Mat mat0 = {array<Z, 2>{3, 0}, array<Z, 2>{1, 2}};
const Mat mat1 = {array<Z, 2>{1, 2}, array<Z, 2>{1, 2}};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> in(N + 1), out(N + 1);

    int l0(0), r0(0);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        if (i == 0)
            l0 = l, r0 = r;
        else {
            in[l].push_back(i);
            out[r].push_back(i);
        }
    }

    SegmentTree<Info> st(vector<Info>(n - 1, {mat0}));

    Z ans = 0;
    for (int i = 0; i <= N; i++) {
        for (auto it : in[i]) {
            st.update(it - 1, {mat1});
        }
        auto Q = st.query(0, n - 1);
        if (l0 <= i && i <= r0)
            ans += Q.x[1][1];
        else
            ans += Q.x[0][1];
        for (auto it : out[i]) {
            st.update(it - 1, {mat0});
        }
    }

    cout << ans << endl;

    return 0;
}