#include <bits/stdc++.h>

using i64 = std::int64_t;

struct mintc {
    int x;
    using Type = int;
    static Type mod;
    mintc() : x(0) {}
    mintc(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    mintc &operator+=(const mintc &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    mintc &operator-=(const mintc &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    mintc &operator*=(const mintc &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }
    mintc &operator/=(const mintc &p) {
        *this *= p.inverse();
        return *this;
    }
    mintc operator-() const { return mintc(-x); }
    mintc operator+(const mintc &p) const { return mintc(*this) += p; }
    mintc operator-(const mintc &p) const { return mintc(*this) -= p; }
    mintc operator*(const mintc &p) const { return mintc(*this) *= p; }
    mintc operator/(const mintc &p) const { return mintc(*this) /= p; }
    bool operator==(const mintc &p) const { return x == p.x; }
    bool operator!=(const mintc &p) const { return x != p.x; }
    mintc inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return mintc(u);
    }
    friend std::ostream &operator<<(std::ostream &os, const mintc &p) {
        return os << p.x;
    }
    friend std::istream &operator>>(std::istream &is, mintc &a) {
        int64_t t;
        is >> t;
        a = mintc(t);
        return (is);
    }
    int get() const { return x; }
    static int get_mod() { return mod; }
    static void set_mod(int md) {
        assert(0 < md && md <= (1LL << 30) - 1);
        mod = md;
    }
};

typename mintc::Type mintc::mod;
using Z = mintc;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, P;
    std::cin >> n >> P;

    Z::set_mod(P);

    std::vector<Z> fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    for (int i = 0; i <= n; i++) invfac[i] = fac[i].inverse();

    auto binom = [&](int n, int m) {
        return (n < 0 || m < 0 || n < m) ? Z(0)
                                         : fac[n] * invfac[n - m] * invfac[m];
    };

    std::vector<Z> d(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) d[j] += i;

    d[0] = Z(n) * Z(n + 1) / Z(2);

    Z ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += d[i] * d[n - i] * binom(n, i);
    }

    std::cout << ans << std::endl;

    return 0;
}