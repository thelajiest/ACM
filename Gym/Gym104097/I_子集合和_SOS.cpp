#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr int P = 998244353;

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

using Z = mint<P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Z> a(n);
    Z allPrid = 1;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        allPrid *= (a[i] + 1);
    }

    Z sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * allPrid / (a[i] + 1);
    }

    std::cout << sum << std::endl;
    return 0;
}

// 有个很明显的生成函数做法：
// 即设 h(x) = (1 + a1 * x) * (1 + a2 * x) * ... * (1 + an * x)
// ans = \sum_{i = 1}^n [x^i]h(x) * i
// 即 ans = h(1)'
// 复合函数求导即可: https://zhuanlan.zhihu.com/p/492629309
// 当然这个题抄无敌的法法塔模版也能过，不过需要一个超快的板子。