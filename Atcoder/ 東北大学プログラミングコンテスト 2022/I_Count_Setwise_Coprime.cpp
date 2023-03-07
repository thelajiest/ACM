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

    int L, R;
    std::cin >> L >> R;

    std::unordered_map<int, Z> mp;
    auto dfs = [&](auto &&self, int l, int r) -> Z {
        if (l >= r) return (l == r && r == 1);
        if (mp.count(l + r)) return mp[l + r];
        Z ret = power<Z>(2, r - l + 1) - Z(1);
        for (int lo = 2, hi; lo <= r; lo = hi + 1) {
            hi = r;

            if (r / lo != 0) hi = std::min(hi, r / (r / lo));
            if ((l - 1) / lo != 0) hi = std::min(hi, (l - 1) / ((l - 1) / lo));

            ret -= Z(hi - lo + 1) * self(self, (l - 1) / lo + 1, r / lo);
        }
        return mp[l + r] = ret;
    };

    std::cout << dfs(dfs, L, R) << std::endl;

    return 0;
}