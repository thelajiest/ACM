#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;

inline i64 binary_gcd(i64 a, i64 b) {
    if (a == 0 || b == 0) return a + b;
    char n = __builtin_ctzll(a);
    char m = __builtin_ctzll(b);
    a >>= n;
    b >>= m;
    n = std::min(n, m);
    while (a != b) {
        i64 d = a - b;
        char s = __builtin_ctzll(d);
        bool f = a > b;
        b = f ? b : a;
        a = (f ? d : -d) >> s;
    }
    return a << n;
}

template <class T>
T mul(T x, T y, T c) {
    if (is_same<int, T>::value) return 1ll * x * y % c;
    if (is_same<i64, T>::value) return __int128(x) * y % c;
    return x * y % c;
}
template <class T>
bool miller(T n) {
    if (n == 2) return 1;

    for (auto p : {2, 3, 5, 7, 11, 13})
        if ([&](T n, int a) -> bool {
                if (n == a) return 1;
                if (n % 2 == 0) return 0;
                auto mpow = [&](T a, T k, T mod) {
                    T res = 1;
                    for (; k; k /= 2, a = mul<T>(a, a, mod))
                        if (k & 1) res = mul<T>(res, a, mod);
                    return res;
                };
                T d = (n - 1) >> __builtin_ctzll(n - 1);
                T r = mpow(a, d, n);

                while (d < n - 1 && r != 1 && r != n - 1)
                    d <<= 1, r = mul<T>(r, r, n);
                return r == n - 1 || d & 1;
            }(n, p) == 0)
            return 0;

    return 1;
}
template <class T>
vector<T> factorization(T n) {
    static mt19937_64 rng(114514);
    auto myrand = [&](i64 a, i64 b) -> i64 {
        return uniform_int_distribution<i64>(a, b)(rng);
    };

    vector<T> res;

    function<void(T)> solve = [&](T x) {
        if (x == 1) return;
        if (miller(x))
            res.push_back(x);
        else {
            T d = [&](T n) {
                auto f = [&](T x) -> T { return (mul<T>(x, x, n) + 1) % n; };
                T x = 0, y = 0, t = 30, prd = 2;
                while (t++ % 40 || binary_gcd(prd, n) == 1) {
                    if (x == y) x = myrand(2, n - 1), y = f(x);
                    T tmp = mul(prd, (x - y) > 0 ? (x - y) : (y - x), n);
                    if (tmp) prd = tmp;
                    x = f(x), y = f(f(y));
                }
                return binary_gcd(prd, n);
            }(x);
            solve(d);
            solve(x / d);
        }
    };

    solve(n);

    return res;
}

namespace Format_Fact {
using i128 = __int128;
struct G {
    i128 a, b;
    G(){};
    G(i128 a, i128 b) : a(a), b(b){};
    G friend operator+(const G &a, const G &b) {
        return {a.a + b.a, a.b + b.b};
    }
    G friend operator-(const G &a, const G &b) {
        return {a.a - b.a, a.b - b.b};
    }
    G friend operator*(const G &a, const G &b) {
        return {a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a};
    }
    bool operator==(const G &x) const { return x.a == a && x.b == b; }
    G operator*(const i128 &t) const { return {a * t, b * t}; }
    G operator/(const i128 &t) const { return {a / t, b / t}; }
    G friend operator/(const G &a, const G &b) {
        i128 len = b.a * b.a + b.b * b.b;
        G c = a * G(b.a, -b.b);
        auto div = [&](i128 a, i128 n) -> i128 {
            i128 now = (a % n + n) % n;
            return ((a - now) / n);
        };
        return {div(2 * c.a + len, 2 * len), div(2 * c.b + len, 2 * len)};
    }
};
static G one = G(1, 0);
template <class T>
T power(T x, i128 b) {
    T res = one;
    while (b) {
        if (b & 1) res = res * x;
        x = x * x;
        b = b / 2;
    }
    return res;
}
G solveprime(i128 p) {
    if (p == 2) return {1, 1};
    i128 t = 1;
    auto qpow = [&](i128 a, i128 b, i128 p) {
        i128 res = 1;
        while (b) {
            if (b & 1) res = res * a % p;
            a = a * a % p;
            b = b / 2;
        }
        return res;
    };
    for (; qpow(t, (p - 1) / 2, p) != p - 1;) t++;
    i128 k = qpow(t, (p - 1) / 4, p);

    function<G(G, G)> Ggcd = [&](G a, G b) -> G {
        if (b.a == 0 && b.b == 0)
            return a;
        else
            return Ggcd(b, a - (a / b) * b);
    };
    auto g = Ggcd({p, 0}, {k, 1});

    if (g.a < 0) g.a = -g.a;
    if (g.b < 0) g.b = -g.b;
    if (g.a > g.b) swap(g.a, g.b);
    return g;
}
vector<G> solvecomposite(i128 n) {
    auto fact = factorization<i64>(n);
    sort(begin(fact), end(fact));

    vector<pair<i128, i64>> prm;
    for (int i = 0, j = 0; i < int(fact.size()); i = j) {
        while (fact[j] == fact[i] && j < int(fact.size())) j++;
        prm.emplace_back(fact[i], j - i);
    }

    vector<G> v{{1, 0}};
    for (auto [p, tmp] : prm) {
        if (p % 4 == 1) {
            G A = solveprime(p);
            G B = {A.a, -A.b};
            auto now = power<G>(A, 2 * tmp);

            vector<G> res;
            for (i64 i = 0; i <= 2 * tmp; i++) {
                for (auto it : v) res.push_back(it * now);
                now = now * B / A;
            }
            swap(v, res);
        } else {
            G now(p, 0);
            now = power<G>(now, tmp);
            for (auto &&it : v) it = it * now;
        }
    }
    for (auto &&[a, b] : v) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
    }
    sort(v.begin(), v.end(), [&](const G &a, const G &b) {
        return make_pair(a.a, a.b) < make_pair(b.a, b.b);
    });
    v.resize(unique(v.begin(), v.end()) - v.begin());

    vector<G> t;
    for (auto [a, b] : v)
        if (a != 0 && b != 0) t.emplace_back(a, b);
    return t;
}
}  // namespace Format_Fact

constexpr i64 mod = 998244353;
struct montgomery64 {
    using mint = montgomery64;
    using i64 = int64_t;
    using u64 = uint64_t;
    using u128 = __uint128_t;

    static u64 mod;
    static u64 r;
    static u64 n2;

    static u64 get_r() {
        u64 ret = mod;
        for (i64 i = 0; i < 5; ++i) ret *= 2 - mod * ret;
        return ret;
    }

    static void set_mod(u64 m) {
        assert(m < (1LL << 62));
        assert((m & 1) == 1);
        mod = m;
        n2 = -u128(m) % m;
        r = get_r();
        assert(r * mod == 1);
    }

    u64 a;

    montgomery64() : a(0) {}
    montgomery64(const int64_t &b) : a(reduce((u128(b) + mod) * n2)){};

    static u64 reduce(const u128 &b) {
        return (b + u128(u64(b) * u64(-r)) * mod) >> 64;
    }

    mint &operator+=(const mint &b) {
        if (i64(a += b.a - 2 * mod) < 0) a += 2 * mod;
        return *this;
    }

    mint &operator-=(const mint &b) {
        if (i64(a -= b.a) < 0) a += 2 * mod;
        return *this;
    }

    mint &operator*=(const mint &b) {
        a = reduce(u128(a) * b.a);
        return *this;
    }

    mint &operator/=(const mint &b) {
        *this *= b.inverse();
        return *this;
    }

    mint operator+(const mint &b) const { return mint(*this) += b; }
    mint operator-(const mint &b) const { return mint(*this) -= b; }
    mint operator*(const mint &b) const { return mint(*this) *= b; }
    mint operator/(const mint &b) const { return mint(*this) /= b; }
    bool operator==(const mint &b) const {
        return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
    }
    bool operator!=(const mint &b) const {
        return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
    }
    mint operator-() const { return mint() - mint(*this); }

    mint pow(u128 n) const {
        mint ret(1), mul(*this);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const mint &b) {
        return os << b.get();
    }

    friend istream &operator>>(istream &is, mint &b) {
        int64_t t;
        is >> t;
        b = montgomery64(t);
        return (is);
    }

    mint inverse() const { return pow(mod - 2); }

    u64 get() const {
        u64 ret = reduce(a);
        return ret >= mod ? ret - mod : ret;
    }

    static u64 get_mod() { return mod; }
};
typename montgomery64::u64 montgomery64::mod, montgomery64::r, montgomery64::n2;
using Z = montgomery64;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    montgomery64::set_mod(mod);
    int _;
    cin >> _;

    while (_--) {
        i64 nn, mm;
        cin >> (nn) >> (mm);
        long long xx = __gcd(nn, mm);
        i128 n(nn), m(mm);
        i128 x = xx;
        auto pr = Format_Fact::solvecomposite(x);
        Z ans = 0;
        for (auto [a, b] : pr) {
            auto picks = [&](i128 a, i128 b) -> Z {
                return (Z(a) * Z(b) - (Z(a) + Z(b) - Z(__gcd(a, b)))) / Z(2);
            };
            auto ra = n / x * a;
            auto rb = m / x * b;
            auto rc = n / x * b;
            auto rd = m / x * a;
            Z res = Z(ra + rb) * Z(rc + rd);
            res -= Z(2) * (Z(ra) * Z(rc) - (picks(ra, rc)));
            res -= Z(2) * (Z(rb) * Z(rd) - (picks(rb, rd)));

            ans += res;
            swap(a, b);
            ra = n / x * a;
            rb = m / x * b;
            rc = n / x * b;
            rd = m / x * a;
            res = Z(ra + rb) * Z(rc + rd);
            res -= Z(2) * (Z(ra) * Z(rc) - (picks(ra, rc)));
            res -= Z(2) * (Z(rb) * Z(rd) - (picks(rb, rd)));
            ans += res;
        }
        ans += Z(n) * Z(m);
        if (n == m)
            cout << ans << '\n';
        else
            cout << ans * Z(2) << '\n';
    }
}
