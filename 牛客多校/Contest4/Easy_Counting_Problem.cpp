#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef vector<int> VI;
typedef pair<int, int> pii;
#define int i64
constexpr int mod = 998244353;

template <int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt<mod>(t);
        return (is);
    }

    int get() const { return x; }

    static constexpr int get_mod() { return mod; }
};

template <typename T>
struct Binomial {
    vector<T> f, g, h;
    Binomial(int MAX = 0) : f(1, T(1)), g(1, T(1)), h(1, T(1)) {
        while (MAX >= (int)f.size()) extend();
    }

    void extend() {
        int n = f.size();
        int m = n * 2;
        f.resize(m);
        g.resize(m);
        h.resize(m);
        for (int i = n; i < m; i++) f[i] = f[i - 1] * T(i);
        g[m - 1] = f[m - 1].inverse();
        h[m - 1] = g[m - 1] * f[m - 2];
        for (int i = m - 2; i >= n; i--) {
            g[i] = g[i + 1] * T(i + 1);
            h[i] = g[i] * f[i - 1];
        }
    }

    T fac(int i) {
        if (i < 0) return T(0);
        while (i >= (int)f.size()) extend();
        return f[i];
    }

    T finv(int i) {
        if (i < 0) return T(0);
        while (i >= (int)g.size()) extend();
        return g[i];
    }

    T inv(int i) {
        if (i < 0) return -inv(-i);
        while (i >= (int)h.size()) extend();
        return h[i];
    }

    T C(int n, int r) {
        if (n < 0 || n < r || r < 0) return T(0);
        return fac(n) * finv(n - r) * finv(r);
    }

    inline T operator()(int n, int r) { return C(n, r); }

    template <typename I>
    T multinomial(const vector<I> &r) {
        static_assert(is_integral<I>::value == true);
        int n = 0;
        for (auto &x : r) {
            if (x < 0) return T(0);
            n += x;
        }
        T res = fac(n);
        for (auto &x : r) res *= finv(x);
        return res;
    }

    template <typename I>
    T operator()(const vector<I> &r) {
        return multinomial(r);
    }

    T C_naive(int n, int r) {
        if (n < 0 || n < r || r < 0) return T(0);
        T ret = T(1);
        r = min(r, n - r);
        for (int i = 1; i <= r; ++i) ret *= inv(i) * (n--);
        return ret;
    }

    T P(int n, int r) {
        if (n < 0 || n < r || r < 0) return T(0);
        return fac(n) * finv(n - r);
    }

    T H(int n, int r) {
        if (n < 0 || r < 0) return T(0);
        return r == 0 ? 1 : C(n + r - 1, r);
    }
};
using mint = ModInt<mod>;
template <typename mint>
struct NTT {
    static constexpr uint32_t get_pr() {
        uint32_t _mod = mint::get_mod();
        using u64 = uint64_t;
        u64 ds[32] = {};
        int idx = 0;
        u64 m = _mod - 1;
        for (u64 i = 2; i * i <= m; ++i) {
            if (m % i == 0) {
                ds[idx++] = i;
                while (m % i == 0) m /= i;
            }
        }
        if (m != 1) ds[idx++] = m;

        uint32_t _pr = 2;
        while (1) {
            int flg = 1;
            for (int i = 0; i < idx; ++i) {
                u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
                while (b) {
                    if (b & 1) r = r * a % _mod;
                    a = a * a % _mod;
                    b >>= 1;
                }
                if (r == 1) {
                    flg = 0;
                    break;
                }
            }
            if (flg == 1) break;
            ++_pr;
        }
        return _pr;
    };

    static constexpr uint32_t mod = mint::get_mod();
    static constexpr uint32_t pr = get_pr();
    static constexpr int level = __builtin_ctzll(mod - 1);
    mint dw[level], dy[level];

    void setwy(int k) {
        mint w[level], y[level];
        w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
        y[k - 1] = w[k - 1].inverse();
        for (int i = k - 2; i > 0; --i)
            w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
        dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
        for (int i = 3; i < k; ++i) {
            dw[i] = dw[i - 1] * y[i - 2] * w[i];
            dy[i] = dy[i - 1] * w[i - 2] * y[i];
        }
    }

    NTT() { setwy(level); }

    void fft4(vector<mint> &a, int k) {
        if ((int)a.size() <= 1) return;
        if (k == 1) {
            mint a1 = a[1];
            a[1] = a[0] - a[1];
            a[0] = a[0] + a1;
            return;
        }
        if (k & 1) {
            int v = 1 << (k - 1);
            for (int j = 0; j < v; ++j) {
                mint ajv = a[j + v];
                a[j + v] = a[j] - ajv;
                a[j] += ajv;
            }
        }
        int u = 1 << (2 + (k & 1));
        int v = 1 << (k - 2 - (k & 1));
        mint one = mint(1);
        mint imag = dw[1];
        while (v) {
            // jh = 0
            {
                int j0 = 0;
                int j1 = v;
                int j2 = j1 + v;
                int j3 = j2 + v;
                for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
                    mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
                    mint t0p2 = t0 + t2, t1p3 = t1 + t3;
                    mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
                    a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;
                    a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;
                }
            }
            // jh >= 1
            mint ww = one, xx = one * dw[2], wx = one;
            for (int jh = 4; jh < u;) {
                ww = xx * xx, wx = ww * xx;
                int j0 = jh * v;
                int je = j0 + v;
                int j2 = je + v;
                for (; j0 < je; ++j0, ++j2) {
                    mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww,
                         t3 = a[j2 + v] * wx;
                    mint t0p2 = t0 + t2, t1p3 = t1 + t3;
                    mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
                    a[j0] = t0p2 + t1p3, a[j0 + v] = t0p2 - t1p3;
                    a[j2] = t0m2 + t1m3, a[j2 + v] = t0m2 - t1m3;
                }
                xx *= dw[__builtin_ctzll((jh += 4))];
            }
            u <<= 2;
            v >>= 2;
        }
    }

    void ifft4(vector<mint> &a, int k) {
        if ((int)a.size() <= 1) return;
        if (k == 1) {
            mint a1 = a[1];
            a[1] = a[0] - a[1];
            a[0] = a[0] + a1;
            return;
        }
        int u = 1 << (k - 2);
        int v = 1;
        mint one = mint(1);
        mint imag = dy[1];
        while (u) {
            // jh = 0
            {
                int j0 = 0;
                int j1 = v;
                int j2 = v + v;
                int j3 = j2 + v;
                for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
                    mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
                    mint t0p1 = t0 + t1, t2p3 = t2 + t3;
                    mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;
                    a[j0] = t0p1 + t2p3, a[j2] = t0p1 - t2p3;
                    a[j1] = t0m1 + t2m3, a[j3] = t0m1 - t2m3;
                }
            }
            // jh >= 1
            mint ww = one, xx = one * dy[2], yy = one;
            u <<= 2;
            for (int jh = 4; jh < u;) {
                ww = xx * xx, yy = xx * imag;
                int j0 = jh * v;
                int je = j0 + v;
                int j2 = je + v;
                for (; j0 < je; ++j0, ++j2) {
                    mint t0 = a[j0], t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];
                    mint t0p1 = t0 + t1, t2p3 = t2 + t3;
                    mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
                    a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;
                    a[j0 + v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;
                }
                xx *= dy[__builtin_ctzll(jh += 4)];
            }
            u >>= 4;
            v <<= 2;
        }
        if (k & 1) {
            u = 1 << (k - 1);
            for (int j = 0; j < u; ++j) {
                mint ajv = a[j] - a[j + u];
                a[j] += a[j + u];
                a[j + u] = ajv;
            }
        }
    }

    void ntt(vector<mint> &a) {
        if ((int)a.size() <= 1) return;
        fft4(a, __builtin_ctz(a.size()));
    }

    void intt(vector<mint> &a) {
        if ((int)a.size() <= 1) return;
        ifft4(a, __builtin_ctz(a.size()));
        mint iv = mint(a.size()).inverse();
        for (auto &x : a) x *= iv;
    }

    vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
        int l = a.size() + b.size() - 1;
        if (min<int>(a.size(), b.size()) <= 40) {
            vector<mint> s(l);
            for (int i = 0; i < (int)a.size(); ++i)
                for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
            return s;
        }
        int k = 2, M = 4;
        while (M < l) M <<= 1, ++k;
        setwy(k);
        vector<mint> s(M), t(M);
        for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i];
        for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i];
        fft4(s, k);
        fft4(t, k);
        for (int i = 0; i < M; ++i) s[i] *= t[i];
        ifft4(s, k);
        s.resize(l);
        mint invm = mint(M).inverse();
        for (int i = 0; i < l; ++i) s[i] *= invm;
        return s;
    }

    void ntt_doubling(vector<mint> &a) {
        int M = (int)a.size();
        auto b = a;
        intt(b);
        mint r = 1, zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
        for (int i = 0; i < M; i++) b[i] *= r, r *= zeta;
        ntt(b);
        copy(begin(b), end(b), back_inserter(a));
    }
};
signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    NTT<mint> ntt;
    auto qpow = [&](i64 a, i64 b) -> i64 {
        i64 res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    };
    int w;
    cin >> w;
    using Poly = vector<mint>;
    constexpr int N = 1e7;
    vector<mint> fac(N + 1), invf(N + 1);
    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invf[N] = qpow(fac[N].get(), mod - 2);
    for (int i = N; i >= 1; i--) {
        invf[i - 1] = invf[i] * i;
    }

    /*
       g[w]=g[w-1]*f(w)+g[w]
       f1+f2
       f1f2
       f1f2f3
   */
    vector<Poly> g(w + 1);
    g[0] = {1};
    Poly f;
    for (int i = 0; i < w; i++) {
        int c;
        cin >> c;
        f.resize(c);
        for (int j = 0; j < c; j++) f[j] = invf[j];
        auto add = [&](Poly &a, const Poly &b) {
            a.resize(max(a.size(), b.size()));
            for (int i = 0; i < a.size(); i++) {
                a[i] = ((i < a.size()) ? a[i] : mint(0)) +
                       ((i < b.size()) ? b[i] : mint(0));
            }
        };
        for (int j = i; j >= 0; j--) add(g[j + 1], ntt.multiply(g[j], f));
    }

    int q;
    cin >> q;

    while (q--) {
        int n;
        cin >> n;
        mint sum = 0;

        for (int c = 0; c <= w; c++) {
            auto Z = mint(qpow(c, n - min(n, (int)g[w - c].size() - 1)));
            for (int i = min(n, (int)g[w - c].size() - 1); i >= 0; i--) {
                if ((w - c) & 1)
                    sum = sum - Z * invf[(n - i)] * g[w - c][i];
                else
                    sum = sum + Z * invf[(n - i)] * g[w - c][i];
                Z *= c;
            }
        }
        sum *= fac[n];
        cout << sum << '\n';
    }
    return 0;
}
