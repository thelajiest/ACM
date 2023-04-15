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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a, b, p, q;
    std::cin >> n >> a >> b >> p >> q;

    // dp[nowA][nowB][x]
    Z pro = Z(p).inverse() * Z(q).inverse();
    std::vector<std::vector<std::vector<Z>>> dp(
        n + 2, std::vector<std::vector<Z>>(n + 2, std::vector<Z>(n + 2)));

    dp[a][b][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int t1 = 1; t1 <= p; t1++) {
                    for (int t2 = 1; t2 <= q; t2++) {
                        dp[std::min(n, j + t1)][std::min(n, k + t2)][i + 1] +=
                            dp[j][k][i] * pro;
                    }
                }
            }
        }
    }

    Z ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k <= n; k++) {
            ans += dp[n][k][i];
        }
    }

    std::cout << ans << std::endl;

    return 0;
}