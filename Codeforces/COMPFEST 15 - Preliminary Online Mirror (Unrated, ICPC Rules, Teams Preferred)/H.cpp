#include <bits/stdc++.h>

using i64 = std::int64_t;

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
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend std::ostream &operator<<(std::ostream &os, const mint &p) {
        return os << p.x;
    }
    friend std::istream &operator>>(std::istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};

constexpr int P = 998244353;
using Z = mint<P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    /*
        1 <= xi <= k
        0 <= xi - x(i-1)  <= k
        ((1-x^(k+1))/(1-x))^n
    */

    int n, k;
    std::cin >> n >> k;

    std::vector<Z> f(n + 1);
    /*
        n,i:
        从l开始：
        i,i+1,i+2,i+3,...,
        l,l+1,l+2,.......,n
        n-l+i<=k
        n-k+i<=l
        l<=n
        \sum_{}n-std::max((n-k+i),1) + 1

    */
    auto f2 = [&](int x) -> Z { return Z(x) * (x + 1) * (2 * x + 1) / 6; };
    auto f1 = [&](int x) -> Z { return Z(x) * (x + 1) / 2; };
    std::vector<Z> fac(n + 1), invf(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * Z(i);
    for (int i = 0; i <= n; i++) invf[i] = fac[i].inverse();

    auto C = [&](int n, int m) {
        if (n < 0 || m < 0 || n < m) return Z(0);
        return fac[n] * invf[m] * invf[n - m];
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            f[i] += power(Z(2), (i - std::max(i - k + j, 1) + 1));
        }
        f[i] -= 1;
    }
    for (int i = 1; i <= n; i++) std::cerr << f[i] << std::endl;
    Z ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += fac[n] / fac[i] * f[n - i];
    }
    std::cout << ans << std::endl;

    return 0;
}