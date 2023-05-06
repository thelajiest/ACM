#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr uint32_t P = 1E9 + 7;

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

template <uint32_t mod>
struct mint {
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    static constexpr u32 get_r() {
        u32 ret = mod;
        for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
        return ret;
    }
    static constexpr u32 r = get_r();
    static constexpr u32 n2 = -u64(mod) % mod;

    u32 a;
    constexpr mint() : a(0) {}
    constexpr mint(const int64_t &b) : a(reduce(u64(b % mod + mod) * n2)){};
    static constexpr u32 reduce(const u64 &b) {
        return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
    }
    constexpr mint &operator+=(const mint &b) {
        if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
        return *this;
    }
    constexpr mint &operator-=(const mint &b) {
        if (i32(a -= b.a) < 0) a += 2 * mod;
        return *this;
    }
    constexpr mint &operator*=(const mint &b) {
        a = reduce(u64(a) * b.a);
        return *this;
    }
    constexpr mint &operator/=(const mint &b) {
        *this *= b.inverse();
        return *this;
    }
    constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
    constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
    constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
    constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
    constexpr bool operator==(const mint &b) const {
        return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr bool operator!=(const mint &b) const {
        return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr mint operator-() const { return mint() - mint(*this); }
    constexpr mint pow(u64 n) const {
        mint ret(1), mul(*this);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }
    constexpr mint inverse() const { return pow(mod - 2); }
    constexpr u32 get() const {
        u32 ret = reduce(a);
        return ret >= mod ? ret - mod : ret;
    }
    static constexpr u32 get_mod() { return mod; }
};
template <class Z>
struct NTT {
    std::vector<int> rev;
    std::vector<Z> roots{0, 1};

    static constexpr int getRoot() {
        auto _mod = Z::get_mod();
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

        int _pr = 2;
        for (;;) {
            int flg = 1;
            for (int i = 0; i < idx; ++i) {
                u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
                for (; b; a = a * a % _mod, b /= 2) {
                    if (b % 2 == 1) r = r * a % _mod;
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

    static constexpr int rt = getRoot();

    void dft(std::vector<Z> &a) {
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
                std::swap(a[i], a[rev[i]]);
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
    void idft(std::vector<Z> &a) {
        int n = a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        Z inv = (1 - (int)Z::get_mod()) / n;
        for (int i = 0; i < n; i++) {
            a[i] *= inv;
        }
    }
    std::vector<Z> multiply(std::vector<Z> a, std::vector<Z> b) {
        int sz = 1, tot = a.size() + b.size() - 1;

        if (tot <= 20) {
            std::vector<Z> ret(tot);
            for (size_t i = 0; i < a.size(); i++)
                for (size_t j = 0; j < b.size(); j++) ret[i + j] += a[i] * b[j];
            return ret;
        }

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

namespace ArbitraryNTT {
using i64 = int64_t;
using u128 = __uint128_t;
constexpr int32_t m0 = 167772161;
constexpr int32_t m1 = 469762049;
constexpr int32_t m2 = 754974721;
using mint0 = mint<m0>;
using mint1 = mint<m1>;
using mint2 = mint<m2>;
constexpr int r01 = mint1(m0).inverse().get();
constexpr int r02 = mint2(m0).inverse().get();
constexpr int r12 = mint2(m1).inverse().get();
constexpr int r02r12 = i64(r02) * r12 % m2;
constexpr i64 w1 = m0;
constexpr i64 w2 = i64(m0) * m1;

template <typename T, typename submint>
std::vector<submint> mul(const std::vector<T> &a, const std::vector<T> &b) {
    static NTT<submint> ntt;
    std::vector<submint> s(a.size()), t(b.size());
    for (int i = 0; i < (int)a.size(); ++i)
        s[i] = i64(a[i] % submint::get_mod());
    for (int i = 0; i < (int)b.size(); ++i)
        t[i] = i64(b[i] % submint::get_mod());
    return ntt.multiply(s, t);
}
template <typename T>
std::vector<int> multiply(const std::vector<T> &s, const std::vector<T> &t,
                          int mod) {
    auto d0 = mul<T, mint0>(s, t);
    auto d1 = mul<T, mint1>(s, t);
    auto d2 = mul<T, mint2>(s, t);
    int n = d0.size();
    std::vector<int> ret(n);
    const int W1 = w1 % mod;
    const int W2 = w2 % mod;
    for (int i = 0; i < n; i++) {
        int n1 = d1[i].get(), n2 = d2[i].get(), a = d0[i].get();
        int b = i64(n1 + m1 - a) * r01 % m1;
        int c = (i64(n2 + m2 - a) * r02r12 + i64(m2 - b) * r12) % m2;
        ret[i] = (i64(a) + i64(b) * W1 + i64(c) * W2) % mod;
    }
    return ret;
}

template <typename mint>
std::vector<mint> multiply(const std::vector<mint> &a,
                           const std::vector<mint> &b) {
    if (a.size() == 0 && b.size() == 0) return {};
    if (std::min<int>(a.size(), b.size()) < 128) {
        std::vector<mint> ret(a.size() + b.size() - 1);
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)b.size(); ++j) ret[i + j] += a[i] * b[j];
        return ret;
    }
    std::vector<int> s(a.size()), t(b.size());
    for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i].get();
    for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i].get();
    std::vector<int> u = multiply<int>(s, t, mint::get_mod());
    std::vector<mint> ret(u.size());
    for (int i = 0; i < (int)u.size(); ++i) ret[i] = mint(u[i]);
    return ret;
}
}  // namespace ArbitraryNTT
template <class Z>
struct Poly {
    std::vector<Z> a;
    Poly() {}
    Poly(int sz, Z val) { a.assign(sz, val); }
    Poly(const std::vector<Z> &a) : a(a) {}
    Poly(const std::initializer_list<Z> &a) : a(a) {}
    int size() const { return a.size(); }
    void resize(int n) { a.resize(n); }
    Z operator[](int idx) const {
        if (idx < size()) {
            return a[idx];
        } else {
            return 0;
        }
    }
    Z &operator[](int idx) { return a[idx]; }
    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k = std::min(k, size());
        return Poly(std::vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(std::vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }

    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        return ArbitraryNTT::multiply(a.a, b.a);
    }
    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    Poly &operator+=(Poly b) { return (*this) = (*this) + b; }
    Poly &operator-=(Poly b) { return (*this) = (*this) - b; }
    Poly &operator*=(Poly b) { return (*this) = (*this) * b; }
    Poly operator/(const Poly &r) const { return Poly(this->a) /= r; }
    Poly rev(int deg = -1) const {
        Poly ret(this->a);
        if (deg != -1) ret.a.resize(deg, Z(0));
        reverse(begin(ret.a), end(ret.a));
        return ret;
    }
    Poly &operator/=(const Poly &r) {
        if (this->size() < r.size()) {
            this->a.clear();
            return *this;
        }
        int n = this->size() - r.size() + 1;
        return *this = (rev().modxk(n) * r.rev().inv(n)).modxk(n).rev(n);
    }
    Poly inv(int m) const {
        Poly x{a[0].inverse()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
};

template <class Z>
Z CoeffofRationalFunction(Poly<Z> P, Poly<Z> Q, i64 k) {
    Z ret = 0;
    if (P.size() >= Q.size()) {
        auto R = P / Q;
        P -= R * Q;
        while (P.size() && P.a.back() == Z(0)) P.a.pop_back();
        if (k < int(R.size())) ret += R[k];
    }
    if (P.a.empty()) return ret;
    P.a.resize(int(Q.size()) - 1);

    while (k > 0) {
        Poly<Z> Q2(Q.a);
        for (int i = 1; i < int(Q2.size()); i += 2) Q2[i] = -Q2[i];
        auto sub = [&](const Poly<Z> &as, bool odd) {
            Poly<Z> bs((as.size() + !odd) / 2, 0);
            for (int i = odd; i < (int)as.size(); i += 2) bs[i >> 1] = as[i];
            return bs;
        };
        P = sub(P * Q2, k & 1);
        Q = sub(Q * Q2, 0);
        k /= 2;
    }

    return ret + P[0];
}

template <typename Z>
std::vector<Z> BerlekampMassey(const std::vector<Z> &s) {
    const int N = (int)s.size();
    std::vector<Z> b, c;
    b.reserve(N + 1);
    c.reserve(N + 1);
    b.push_back(Z(1));
    c.push_back(Z(1));
    Z y = Z(1);
    for (int ed = 1; ed <= N; ed++) {
        int l = int(c.size()), m = int(b.size());
        Z x = 0;
        for (int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
        b.emplace_back(Z(0));
        m++;
        if (x == Z(0)) continue;
        Z freq = x / y;
        if (l < m) {
            auto tmp = c;
            c.insert(begin(c), m - l, Z(0));
            for (int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
            b = tmp;
            y = x;
        } else {
            for (int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
        }
    }
    std::reverse(begin(c), end(c));
    return c;
}

using Z = mint<P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Z> preSolve = {1,       1,       3,       10,       23,
                               62,      170,     441,     1173,     3127,
                               8266,    21937,   58234,   154390,   409573,
                               1086567, 2882021, 7645046, 20279829, 53794224};

    auto bm = BerlekampMassey<Z>(preSolve);

    i64 n;
    std::cin >> n;

    auto Q = ArbitraryNTT::multiply(bm, preSolve);
    Q.resize(bm.size());
    auto ans = CoeffofRationalFunction<Z>(Q, bm, n);
    std::cout << ans.get() << std::endl;

    return 0;
}