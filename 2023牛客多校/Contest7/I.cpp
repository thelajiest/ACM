#include <bits/stdc++.h>

#include <format>
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
constexpr int T = 20;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> s(n);
    for (int i = 0; i < n; i++) {
        std::string _;
        std::cin >> _;
        for (auto p : _) {
            if (p == '0') s[i].push_back(0);
            if (p == '1') s[i].push_back(1);
            if (p == '?') s[i].push_back(2);
        }
    }

    std::sort(begin(s), end(s), [&](const auto &a, const auto &b) {
        return a.size() < b.size();
    });

    auto solve = [&](const std::vector<std::vector<int>> &s) -> Z {
        int n = s.size();
        int len = s[0].size();
        if (len <= T) {
            i64 ans = 0;
            for (int i = 0; i < (1 << len); i++) {
                std::vector<int> cur(len);
                for (int j = 0; j < len; j++) {
                    if ((i >> j) & 1) cur[j] = 1;
                }
                for (int j = 0; j < n; j++) {
                    bool ok = true;
                    for (int k = 0; k < len; k++) {
                        if (s[j][k] != 2 && s[j][k] != cur[k]) ok = false;
                    }
                    if (ok) {
                        ans++;
                        break;
                    }
                }
            }
            return ans;
        } else {
            std::vector<Z> p(len + 1);
            p[0] = 1;
            for (int i = 1; i <= len; i++) p[i] = p[i - 1] * 2;
            Z ans = 0;
            for (int i = 1; i < (1 << n); i++) {
                std::vector<int> cur(len, -1);
                bool ok = true;
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    if ((i >> j) & 1) {
                        cnt++;
                        for (int t = 0; t < len; t++) {
                            if (cur[t] == -1)
                                cur[t] = s[j][t];
                            else {
                                if (cur[t] == 2 && s[j][t] != 2)
                                    cur[t] = s[j][t];
                                if (cur[t] != 2 && cur[t] != s[j][t] &&
                                    s[j][t] != 2) {
                                    ok = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (!ok) break;
                }
                if (!ok) continue;
                int sum = std::count(begin(cur), end(cur), 2);
                if (cnt % 2 == 1)
                    ans += p[sum];
                else
                    ans -= p[sum];
            }
            return ans;
        }
    };

    Z ans = 0;
    for (int l = 0, r; l < n; l = r) {
        r = l;
        while (r < n && s[r].size() == s[l].size()) r++;
        ans += solve({s.begin() + l, s.begin() + r});
    }
    return 0;
}