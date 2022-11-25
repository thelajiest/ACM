#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int mod = 1E9 + 7;
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
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
    friend istream &operator>>(istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};
using Z = mint<mod>;
void solve() {
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> adj(n);
    vector<pair<i64, i64>> edge;
    vector<i64> deg(n);
    for (i64 i = 1; i <= m; i++) {
        i64 x, y;
        cin >> x >> y;
        x--, y--;
        edge.emplace_back(x, y);
        adj[x].push_back(y);
        adj[y].push_back(x);
        deg[x]++, deg[y]++;
    }

    auto solveCir4 = [&](const vector<vector<i64>> &adj) -> Z {
        Z ans = 0;
        vector<i64> kth(n), rk(n);
        vector<i64> cnt(n);
        vector<vector<i64>> key(n);
        iota(begin(kth), end(kth), 0);
        sort(begin(kth), end(kth),
             [&](auto x, auto y) { return deg[x] < deg[y]; });
        for (i64 i = 0; i < n; i++) rk[kth[i]] = i;

        for (i64 u = 0; u < n; u++) {
            for (i64 v : adj[u]) {
                if (rk[v] > rk[u]) key[u].emplace_back(v);
            }
        }
        for (i64 u = 0; u < n; u++) {
            for (i64 v : adj[u]) {
                for (i64 w : key[v]) {
                    if (rk[w] > rk[u]) {
                        ans += cnt[w]++;
                    }
                }
            }
            for (i64 v : adj[u]) {
                for (i64 w : key[v]) {
                    if (rk[w] > rk[u]) --cnt[w];
                }
            }
        }
        return ans;
    };

    auto solveCir3 = [&](const vector<pair<i64, i64>> &Edge) -> Z {
        Z ans = 0;
        vector<vector<i64>> G(n);
        vector<i64> p(n, -1);
        for (auto &[u, v] : Edge) {
            if (deg[u] < deg[v] || (deg[u] == deg[v] && u < v))
                G[u].push_back(v);
            else
                G[v].push_back(u);
        }
        for (i64 x = 0; x < n; x++) {
            for (i64 y : G[x]) p[y] = x;
            for (i64 y : G[x]) {
                for (i64 z : G[y])
                    if (p[z] == x) ans += 1;
            }
        }
        return ans;
    };

    // For three on mid ,one on vertex
    Z c3 = Z(3) * solveCir3(edge);
    // For four on mid
    Z c4 = solveCir4(adj);

    Z ans = c3 + c4;
    for (i64 i = 0; i < n; i++) {
        ans += Z(deg[i]) * Z(deg[i] - 1) / Z(2);
        // count itself C(n,2)
        // V
    }
    // m is edge with 3(two vertex and one mid) *(all possible except 3(itself))

    ans += Z(m) * Z(n + m - 3);
    cout << ans << '\n';

    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}