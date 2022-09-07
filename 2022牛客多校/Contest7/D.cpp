#include <bits/stdc++.h>
using namespace std;
using i64 = __int128;
#define int i64
using VI = vector<int>;
using pii = pair<int, int>;

namespace Factorization {
static mt19937_64 rng(114514);
inline i64 mul(i64 a, i64 b, i64 c) {
    i64 s = a * b - c * i64((long double)a / c * b + 0.5);
    return s < 0 ? s + c : s;
}

i64 mPow(i64 a, i64 k, i64 mod) {
    i64 res = 1;
    for (; k; k >>= 1, a = mul(a, a, mod))
        if (k & 1) res = mul(res, a, mod);
    return res;
}

bool test(i64 n, int a) {
    if (n == a) return 1;
    if (n % 2 == 0) return 0;

    i64 d = (n - 1) >> __builtin_ctzll(n - 1);
    i64 r = mPow(a, d, n);

    while (d < n - 1 && r != 1 && r != n - 1) d <<= 1, r = mul(r, r, n);
    return r == n - 1 || d & 1;
}
bool mii64er(i64 n) {
    if (n == 2) return 1;
    for (auto p : VI{2, 3, 5, 7, 11, 13})
        if (test(n, p) == 0) return 0;
    return 1;
}
long long myrand(i64 a, i64 b) {
    return uniform_int_distribution<long long>(a, b)(rng);
}
i64 poi64ard(i64 n) {
    auto f = [&](i64 x) { return ((__int128)x * x + 1) % n; };
    auto babs = [&](i64 x) {
        if (x > 0)
            return x;
        else
            return -x;
    };
    i64 x = 0, y = 0, t = 30, prd = 2;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        // speedup: don't take __gcd in each iteration.
        if (x == y) x = myrand(2, n - 1), y = f(x);
        i64 tmp = mul(prd, babs(x - y), n);
        if (tmp) prd = tmp;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<i64> work(i64 n) {
    vector<i64> res;

    function<void(i64)> solve = [&](i64 x) {
        if (x == 1) return;
        if (mii64er(x))
            res.push_back(x);
        else {
            i64 d = poi64ard(x);
            solve(d);
            solve(x / d);
        }
    };
    solve(n);
    return res;
}
}  // namespace Factorization
namespace Format_Fact {
using i128 = __int128;

inline pair<i64, i64> solve(i64 p) {
    if (p == 2) return {1, 1};
    auto Mul = [&](i64 a, i64 b) -> i128 { return i128(a) * b; };
    function<pair<i64, i64>(pair<i64, i64>, pair<i64, i64>)> gcd =
        [&](pair<i64, i64> a, pair<i64, i64> b) -> pair<i64, i64> {
        if (b == make_pair((i64)0, (i64)0)) return a;

        i128 k = Mul(b.first, b.first) + Mul(b.second, b.second);
        i128 u = Mul(a.first, b.first) + Mul(a.second, b.second);
        i128 v = Mul(a.second, b.first) - Mul(a.first, b.second);
        pair<i64, i64> q = make_pair(llround(u / (long double)(k)),
                                     llround(v / (long double)(k)));
        return gcd(
            b, make_pair(a.first - q.first * b.first + q.second * b.second,
                         a.second - q.first * b.second - q.second * b.first));
    };

    auto fpow = [&](i64 a, i64 b) -> i64 {
        i64 res = 1;

        for (; b; b >>= 1LL, a = Mul(a, a) % p)
            if (b & 1) res = Mul(res, a) % p;

        return res;
    };
    i64 t = 1, k;
    for (; fpow(t, (p - 1) >> 1LL) != p - 1;) t++;
    k = fpow(t, (p - 1) >> 2LL);
    pair<i64, i64> g = gcd(make_pair(p, 0), make_pair(k, 1));
    i64 a = g.first, b = g.second;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a > b) a ^= b ^= a ^= b;
    return {a, b};
}
}  // namespace Format_Fact
vector<pair<i64, i64>> GaussInger_Work(i64 n) {
    auto fact = Factorization::work(n);
    sort(fact.begin(), fact.end());

    vector<pair<i64, i64>> ret;
    fact.resize(unique(fact.begin(), fact.end()) - fact.begin());
    for (auto p : fact) {
        /*
            a^2+b^2=p
            n^2=p^2q^2; (q=n/p) root
            n^2=(a^2+b^2)^2
           q^2=(q^2a^4+2q^2(ab)^2+q^2b^4)=q^2((a^2-b^2)^2+(2ab)^2)
        */
        if ((p - 1) % 4 == 0) {
            auto [a, b] = Format_Fact::solve(p);
            if (a < b) swap(a, b);
            ret.emplace_back((a * a - b * b) * (n / p), (2 * a * b) * (n / p));
        }
    }
    return ret;
}
constexpr int mod = 998'244'353;
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
        return os << (long long)p.x;
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
// sum_{0 <= i < N} (ai + b) // m
using Z = ModInt<mod>;
Z sum_of_floor(i64 n, i64 m, i64 a, i64 b) {
    Z ret = 0;
    if (a >= m) ret += (n - 1) * n * (a / m) / 2, a %= m;
    if (b >= m) ret += n * (b / m), b %= m;
    i64 y = (a * n + b) / m;
    if (y == 0) return ret;
    i64 x = y * m - b;
    ret += (n - (x + a - 1) / a) * y;
    ret += sum_of_floor(y, a, m, (a - x % a) % a);
    return ret;
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    signed _;
    cin >> _;

    while (_--) {
        long long nn, mm;
        cin >> (nn) >> (mm);
        long long xx = __gcd(nn, mm);
        i64 n(nn), m(mm);
        i64 x = xx;
        auto pr = GaussInger_Work(x);
        Z ans = 0;
        for (auto [a, b] : pr) {
            auto ra = n / x * a;
            auto rb = m / x * b;
            auto rc = n / x * b;
            auto rd = m / x * a;
            Z res = Z(ra + rb) * Z(rc + rd);
            res -= Z(2) * (Z(ra) * Z(rc) - (sum_of_floor(ra, a, b, 0)));
            res -= Z(2) * (Z(rb) * Z(rd) - (sum_of_floor(rb, b, a, 0)));

            ans += res;
            swap(a, b);
            ra = n / x * a;
            rb = m / x * b;
            rc = n / x * b;
            rd = m / x * a;
            res = Z(ra + rb) * Z(rc + rd);
            res -= Z(2) * (Z(ra) * Z(rc) - (sum_of_floor(ra, a, b, 0)));
            res -= Z(2) * (Z(rb) * Z(rd) - (sum_of_floor(rb, b, a, 0)));
            ans += res;
        }
        ans += Z(n) * Z(m);
        if (n == m)
            cout << ans << '\n';
        else
            cout << ans * Z(2) << '\n';
    }
}