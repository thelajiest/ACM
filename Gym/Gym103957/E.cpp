#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <class T>
T power(T a, int b) {
    T res = 1;
    while (b) {
        if (b % 2 == 1) res *= a;
        a *= a;
        b /= 2;
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

constexpr int mod = 1E9 + 7;
using Z = mint<mod>;

vector<int> prime_sieve(int N) {
    vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}

template <class T>
vector<T> mf_sieve(int n, function<T(i64, i64, i64)> f) {
    /*
        ##pragma f is a multiplicative-function
        f(n,p,c) <-> n=p^c
    */
    vector<T> ans(n + 1, T());
    vector<int> ps = prime_sieve(n);
    int p(ps.size());

    function<void(int, i64, T)> dfs = [&](int i, i64 x, T y) {
        ans[x] = y;
        if (y == T()) return;
        for (int j = i + 1; j < p; j++) {
            i64 nx = x * ps[j];
            i64 dx = ps[j];
            if (nx > n) break;
            for (int c = 1; nx <= n; nx *= ps[j], dx *= ps[j], ++c)
                dfs(j, nx, y * f(dx, ps[j], c));
        }
    };
    ans[1] = 1;
    dfs(-1, 1, 1);
    return ans;
};

template <class T>
vector<T> OsakDivisors(T x) {
    auto primes = prime_sieve(sqrt(x) + 10);

    vector<pair<T, int>> lt;
    for (auto p : primes) {
        if (1LL * p * p > x) break;
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        if (cnt >= 1) lt.emplace_back(p, cnt);
    }
    if (x > 1) lt.emplace_back(x, 1);
    vector<T> div;
    auto dfs = [&](auto rec, int i, T c) {
        if (i == int(lt.size())) {
            div.push_back(c);
            return;
        }
        for (int j = 0; j <= lt[i].second; j++) {
            rec(rec, i + 1, c);
            c *= lt[i].first;
        }
    };
    dfs(dfs, 0, 1);
    return div;
}
vector<Z> euler;
constexpr int N = 1E6;

void solve() {
    int k, r, c;
    cin >> k >> r >> c;

    vector<int> p(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> p[i];
        p[i] += 1;
    }

    vector<int> vis(k + 1);

    unordered_map<int, int> mp;

    for (int i = 1; i <= k; i++) {
        if (!vis[i]) {
            int cnt = 0;
            int now = p[i];
            while (!vis[now]) {
                cnt++;
                vis[now] = 1;
                now = p[now];
            }
            mp[cnt]++;
        }
    }
    auto divr = OsakDivisors(r);
    auto divc = OsakDivisors(c);
    Z ans = 0;
    for (auto p1 : divr) {
        for (auto p2 : divc) {
            i64 Lcm = std::lcm<i64>(p1, p2);
            i64 d = 1LL * r * c / Lcm;
            d %= (mod - 1);

            i64 col = 0;
            for (auto [len, cnt] : mp) {
                if (Lcm % len == 0) {
                    col += 1LL * len * cnt;
                }
            }
            ans += euler[p1] * euler[p2] * power(Z(col), d);
        }
    }

    cout << ans / Z(r) / Z(c) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    euler =
        mf_sieve<Z>(N, [&](i64 n, i64 p, i64 c) { return Z(n) - Z(n / p); });

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}