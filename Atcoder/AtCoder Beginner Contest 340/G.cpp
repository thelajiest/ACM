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

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i + 1 < N; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<std::map<int, Z>> dp(N);
    Z ans = 0;

    auto dfs = [&](auto &&self, int x, int par) -> void {
        int heavyChild = -1;
        for (auto y : adj[x]) {
            if (y == par) continue;
            self(self, y, x);
            if (heavyChild == -1 || dp[heavyChild].size() < dp[y].size()) {
                heavyChild = y;
            }
            if (dp[y].find(A[x]) != dp[y].end()) {
                ans += dp[y][A[x]];
            }
        }

        if (heavyChild != -1) {
            std::swap(dp[x], dp[heavyChild]);
            for (auto y : adj[x]) {
                if (y == par || y == heavyChild) continue;
                for (auto [col, cnt] : dp[y]) {
                    if (dp[x].find(col) != dp[x].end()) {
                        ans += dp[x][col] * cnt;
                        dp[x][col] += dp[x][col] * cnt + cnt;
                    } else {
                        dp[x].insert({col, cnt});
                    }
                }
            }
        }

        if (dp[x].find(A[x]) != dp[x].end()) {
            dp[x][A[x]] += 1;
        } else {
            dp[x].insert({A[x], 1});
        }
        ans += 1;
    };

    dfs(dfs, 0, -1);
    std::cout << ans << std::endl;

    return 0;
}