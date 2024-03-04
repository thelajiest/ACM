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

constexpr int P = 1E9 + 7;
using Z = mint<P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    i64 L, R;
    std::cin >> n >> L >> R;

    std::vector<i64> A(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    auto solve = [&](i64 x) -> Z {
        std::map<i64, Z> mp;
        mp.insert({x, 1});

        for (int i = 0; i < n; i++) {
            auto bound = mp.lower_bound(A[i]);
            if (bound == mp.end()) continue;
            Z cnt = 0;
            for (auto it = bound; it != mp.end(); it++) {
                auto [y, sum] = *it;
                mp[y % A[i]] += sum;
                cnt += sum * Z(y / A[i]);
            }
            mp.erase(bound, mp.end());
            mp[A[i] - 1] += cnt;
        }

        Z ret = 0;
        for (auto [x, cnt] : mp) {
            ret += Z(x) * Z(x + 1) * cnt / Z(2);
        }
        return ret;
    };

    if (L == 0) {
        std::cout << solve(R) << std::endl;
    } else {
        std::cout << solve(R) - solve(L - 1) << std::endl;
    }

    return 0;
}