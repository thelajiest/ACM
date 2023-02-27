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

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> card(n + 1);
    for (int i = 1; i <= n; i++) {
        auto &[x, y] = card[i];
        std::cin >> x >> y;
    }

    std::vector<std::array<Z, 2>> dp(n + 1);
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        auto [x, y] = card[i];
        auto [xx, yy] = card[i - 1];
        dp[i][0] +=
            ((x == xx) ? 0 : dp[i - 1][0]) + ((x == yy) ? 0 : dp[i - 1][1]);
        dp[i][1] +=
            ((y == xx) ? 0 : dp[i - 1][0]) + ((y == yy) ? 0 : dp[i - 1][1]);
    }

    std::cout << dp[n][0] + dp[n][1] << std::endl;

    return 0;
}