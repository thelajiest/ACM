#include <bits/extc++.h>
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
std::vector<int> prime_sieve(int N) {
    std::vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    std::vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}
template <class T>
std::vector<T> mf_sieve(int n, std::function<T(i64, i64, i64)> f) {
    /*
        ##pragma f is a multiplicative-function
        f(n,p,c) <-> n=p^c
    */
    std::vector<T> ans(n + 1, T());
    std::vector<int> ps = prime_sieve(n);
    int p(ps.size());

    std::function<void(int, i64, T)> dfs = [&](int i, i64 x, T y) {
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

constexpr int th = 5E5;
std::vector<std::array<Z, 11>> psum(th);
void solve() {
    i64 n, k;
    std::cin >> n >> k;

    std::vector<std::vector<Z>> C(k + 1, std::vector<Z>(k + 1, 0));
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= i; j++) {
            if (0 == j || i == j)
                C[i][j] = 1;
            else
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    std::vector<Z> p(k + 1), invp(k + 1);
    p[0] = 1;
    for (int i = 1; i <= k; i++) p[i] = p[i - 1] * 2;
    for (int i = 0; i <= k; i++) invp[i] = (p[i] - 1).inverse();
    auto f = [&](i64 n) -> Z {
        Z ret = 0;
        for (int j = 0; j <= k; j++) {
            Z t = 0;
            if (j == 0) {
                t = n;
            } else {
                // t = (p2[j] - p[j]) * invp[j];
                t = (power(Z(2), 1LL * (n + 1) * j % (P - 1)) - p[j]) * invp[j];
            }
            if ((k - j) % 2 == 0) {
                ret += C[k][j] * t;
            } else {
                ret -= C[k][j] * t;
            }
        }
        return ret;
    };

    __gnu_pbds::gp_hash_table<i64, Z> sum;

    auto dfs = [&](auto &&self, i64 x) -> Z {
        if (x < th) return psum[x][k];
        if (sum[x].get()) return sum[x];

        Z ret = f(x);
        for (i64 l = 2, r; l <= x; l = r + 1) {
            r = x / (x / l);
            ret -= self(self, x / l) * (r - l + 1);
        }
        return sum[x] = ret;
    };

    Z ans = 0;
    for (i64 l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (dfs(dfs, r) - dfs(dfs, l - 1)) * Z(n / l) * Z(n / l);
    }
    std::cout << ans << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    auto mu = mf_sieve<Z>(th, [&](i64 n, i64 p, i64 c) -> Z {
        return c == 0 ? 1 : c == 1 ? -1 : 0;
    });

    for (int k = 0; k <= 10; k++) {
        for (int i = 1; i < th; i++) {
            Z t = 2;
            for (int j = 1; j * i < th; j++) {
                psum[j * i][k] += mu[i] * power(t - 1, k);
                t *= Z(2);
            }
        }
    }
    for (int k = 0; k <= 10; k++) {
        for (int i = 1; i < th; i++) psum[i][k] += psum[i - 1][k];
    }

    while (T--) {
        solve();
    }

    return 0;
}