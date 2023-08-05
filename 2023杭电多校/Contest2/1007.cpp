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
constexpr int P = 1000000007;
using Z = mint<P>;
constexpr int N = 1001;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::bitset<N>> adj(n);
    std::vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        assert(x != y);
        x--, y--;
        adj[x][y] = 1;
        adj[y][x] = 1;
    }
    for (int i = 0; i < n; i++) deg[i] = adj[i].count();
    const Z inv4 = Z(24).inverse();
    const Z inv2 = Z(2).inverse();
    Z ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int cnt1 = deg[i], cnt2 = deg[j], cnt = (adj[i] & adj[j]).count();

            if (adj[i][j]) {
                cnt1--;
                cnt2--;
            }
            if (cnt >= 4) {
                if (cnt1 >= 6)
                    ans += Z(cnt) * Z(cnt - 1) * Z(cnt - 2) * Z(cnt - 3) *
                           inv4 * Z(cnt1 - 4) * Z(cnt1 - 5) * inv2;
                if (cnt2 >= 6)
                    ans += Z(cnt) * Z(cnt - 1) * Z(cnt - 2) * Z(cnt - 3) *
                           inv4 * Z(cnt2 - 4) * Z(cnt2 - 5) * inv2;
            }
        }
    }
    std::cout << ans * inv2 << '\n';
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}