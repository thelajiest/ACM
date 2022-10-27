#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
template <class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
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
using Z = mint<mod>;

template <class Z, int rt>
struct NTT {
    vector<int> rev;
    vector<Z> roots{0, 1};
    void dft(vector<Z> &a) {
        int n = a.size();

        if (int(rev.size()) != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++) {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        for (int i = 0; i < n; i++) {
            if (rev[i] < i) {
                swap(a[i], a[rev[i]]);
            }
        }
        if (int(roots.size()) < n) {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n) {
                Z e = power(Z(rt), (Z::get_mod() - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    roots[2 * i] = roots[i];
                    roots[2 * i + 1] = roots[i] * e;
                }
                k++;
            }
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    Z u = a[i + j];
                    Z v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v;
                    a[i + j + k] = u - v;
                }
            }
        }
    }
    void idft(vector<Z> &a) {
        int n = a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        Z inv = (1 - Z::get_mod()) / n;
        for (int i = 0; i < n; i++) {
            a[i] *= inv;
        }
    }
    vector<Z> multiply(vector<Z> a, vector<Z> b) {
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) {
            sz *= 2;
        }

        a.resize(sz), b.resize(sz);
        dft(a), dft(b);

        for (int i = 0; i < sz; ++i) {
            a[i] = a[i] * b[i];
        }

        idft(a);
        a.resize(tot);
        return a;
    }
};

void solve() {
    int n, l, m;
    cin >> n >> l >> m;
    vector<Z> a(n);
    for (int i = n - 1; i >= 0; i--) cin >> a[i];
    vector<Z> g(n);
    g[0] = 1;
    for (int i = 0; i < n - 1; i++) g[i + 1] = g[i] * Z(m + i) / Z(i + 1);

    vector<Z> h(n);
    Z comb = 1;
    for (int i = 0; l * i < n; i++) {
        if (i & 1)
            h[l * i] = -comb;
        else
            h[l * i] = comb;
        comb = comb / Z(i + 1) * Z(m - i);
    }

    static NTT<Z, 3> ntt;
    auto conv = ntt.multiply(g, h);
    conv = ntt.multiply(conv, a);
    for (int i = 0; i < n; i++) {
        cout << conv[n - i - 1] << " \n"[i == n - 1];
    }
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}