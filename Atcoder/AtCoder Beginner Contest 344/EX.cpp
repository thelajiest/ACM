// This problem is almost the same as ICPC Online Contest 2022 #1 Problem F
// f * I^k = e
// f = e * (I^-1)^k = mu ^ k
// sum_{i = 1} ^ n f(i)

// consider bell series then use min25 sieve is fine
#include <bits/stdc++.h>
using i64 = std::int64_t;

std::vector<int> prime_sieve(int N) {
    std::vector<int> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    std::vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++) {
        if (sieve[i]) ret.push_back(p);
    }
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
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

constexpr int mod = 998244353;
using Z = mint<mod>;

template <typename T, T (*f)(i64, i64)>
struct MfPrefixSum {
    i64 M, sq, s;
    std::vector<int> p;
    int ps;
    std::vector<T> buf;
    T ans;

    MfPrefixSum(i64 m) : M(m) {
        assert(m < (1LL << 42));
        sq = sqrt(M);
        while (sq * sq > M) sq--;
        while ((sq + 1) * (sq + 1) <= M) sq++;

        if (M != 0) {
            i64 hls = md(M, sq);
            if (hls != 1 && md(M, hls - 1) == sq) hls--;
            s = hls + sq;

            p = prime_sieve(sq);
            ps = p.size();
            ans = T{};
        }
    }
    // T PSumPower(i64 n, int k) {
    //     std::vector<T> now(k + 2);
    //     now[0] = T(0);
    //     for (int i = 1; i < k + 2; i++) {
    //         T res = i;
    //         now[i] = now[i - 1] + power(res, k);
    //     }
    //     return LagrangeInterpolation<T>(now, n);
    // }
    std::vector<T> pi_table() {
        //\sum_{p\in prime \and p\leq m} p^0
        if (M == 0) return {};
        i64 hls = md(M, sq);
        if (hls != 1 && md(M, hls - 1) == sq) hls--;

        std::vector<i64> hl(hls);
        for (int i = 1; i < hls; i++) hl[i] = md(M, i) - 1;

        std::vector<int> hs(sq + 1);
        std::iota(begin(hs), end(hs), -1);

        int pi = 0;
        for (auto &x : p) {
            i64 x2 = i64(x) * x;
            i64 imax = std::min<i64>(hls, md(M, x2) + 1);
            for (i64 i = 1, ix = x; i < imax; ++i, ix += x) {
                hl[i] -= (ix < hls ? hl[ix] : hs[md(M, ix)]) - pi;
            }
            for (int n = sq; n >= x2; n--) hs[n] -= hs[md(n, x)] - pi;
            pi++;
        }

        std::vector<T> res;
        res.reserve(2 * sq + 10);
        for (auto &x : hl) res.push_back(x);
        for (int i = hs.size(); --i;) res.push_back(hs[i]);
        assert((int)res.size() == s);
        return res;
    }
    // std::vector<T> prime_sum_table(int k) {
    //     //\sum_{p\in prime \and p\leq m} p^k
    //     if (M == 0) return {};
    //     i64 hls = md(M, sq);
    //     if (hls != 1 && md(M, hls - 1) == sq) hls--;

    //     std::vector<T> h(s);
    //     T inv2 = T{2}.inverse();
    //     for (int i = 1; i < hls; i++) {
    //         T x = md(M, i);
    //         h[i] = PSumPower(x.get(), k) - 1;
    //     }
    //     for (int i = 1; i <= sq; i++) {
    //         T x = i;
    //         h[s - i] = PSumPower(x.get(), k) - 1;
    //     }

    //     for (auto &x : p) {
    //         T xt = x;
    //         xt = power(xt, k);
    //         T pi = h[s - x + 1];
    //         i64 x2 = i64(x) * x;
    //         i64 imax = std::min<i64>(hls, md(M, x2) + 1);
    //         i64 ix = x;
    //         for (i64 i = 1; i < imax; ++i, ix += x) {
    //             h[i] -= ((ix < hls ? h[ix] : h[s - md(M, ix)]) - pi) * xt;
    //         }
    //         for (int n = sq; n >= x2; n--) {
    //             h[s - n] -= (h[s - md(n, x)] - pi) * xt;
    //         }
    //     }

    //     assert((int)h.size() == s);
    //     return h;
    // }

    void dfs(int i, int c, i64 prod, T cur) {
        ans += cur * f(p[i], c + 1);
        i64 lim = md(M, prod);
        if (lim >= 1LL * p[i] * p[i]) dfs(i, c + 1, p[i] * prod, cur);
        cur *= f(p[i], c);
        ans += cur * (buf[idx(lim)] - buf[idx(p[i])]);
        int j = i + 1;
        // M < 2**42 -> p_j < 2**21 -> (p_j)^3 < 2**63
        for (; j < ps && 1LL * p[j] * p[j] * p[j] <= lim; j++) {
            dfs(j, 1, prod * p[j], cur);
        }
        for (; j < ps && 1LL * p[j] * p[j] <= lim; j++) {
            T sm = f(p[j], 2);
            int id1 = idx(md(lim, p[j])), id2 = idx(p[j]);
            sm += f(p[j], 1) * (buf[id1] - buf[id2]);
            ans += cur * sm;
        }
    }

    T run(std::vector<T> &fprime) {
        if (M == 0) return {};
        set_buf(fprime);
        assert((int)buf.size() == s);
        ans = buf[idx(M)] + 1;
        for (int i = 0; i < ps; i++) dfs(i, 1, p[i], 1);
        return ans;
    }

   private:
    i64 md(i64 n, i64 d) { return double(n) / d; }
    i64 idx(i64 n) { return n <= sq ? s - n : md(M, n); }
    void set_buf(std::vector<T> &_buf) { swap(buf, _buf); }
};

constexpr int N = 60;

i64 n, m;
std::vector<Z> inv(N + 1);
Z f(i64 p, i64 t) {
    // bell series (p ^ t): [x ^ t](1 - x) ^ m ->  C(m, t) * (-1) ^ t
    /*
        (-1) ^ t * C(m, t)
    */
    Z res = 1;
    for (i64 base = m, now = 1; now <= t; now++, base--) {
        res *= Z(base);
    }
    for (int i = 1; i <= t; i++) res *= inv[i];

    if (t & 1) res = -res;
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> m >> n;
    for (int i = 1; i <= 60; i++) {
        inv[i] = Z(i).inverse();
    }
    MfPrefixSum<Z, f> solve(n);
    auto q = solve.pi_table();

    for (auto &qq : q) {
        qq *= Z(m);
        qq = -qq;
    }

    auto ans = solve.run(q);
    std::cout << ans << std::endl;

    return 0;
}