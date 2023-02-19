#include <bits/stdc++.h>

using i64 = std::int64_t;

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

constexpr int N = 1E6 + 1;
std::vector<Z> fac(N), invfac(N);

template <class T = Z>
T comb(int n, int m) {
    if (n < 0 || m < 0 || n < m) return T(0);
    return fac[n] * invfac[n - m] * invfac[m];
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    auto all = [&](int n, int m) -> Z {
        return comb(n, 4) * comb(m, 2) * comb(m, 2);
    };

    Z ans = all(n, m) + all(m, n);
    ans -= comb(n, 4) * comb(m, 4);

    std::cout << ans << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = Z(i) * fac[i - 1];
    for (int i = 0; i < N; i++) invfac[i] = fac[i].inverse();

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}