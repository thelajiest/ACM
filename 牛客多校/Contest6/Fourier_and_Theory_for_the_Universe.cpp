#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<i64>;
using pii = pair<i64, i64>;
vector<i64> prime_enumerate(i64 N) {
    vector<bool> sieve(N / 3 + 1, 1);
    for (i64 p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (i64 q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    vector<i64> ret{2, 3};
    for (i64 p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}
template <typename T>
struct mf_prefix_sum {
    using i64 = long long;

    i64 M, sq, s;
    vector<i64> p;
    i64 ps;
    vector<T> buf;
    T ans;

    mf_prefix_sum(i64 m) : M(m) {
        assert(m < (1LL << 42));
        sq = sqrt(M);
        while (sq * sq > M) sq--;
        while ((sq + 1) * (sq + 1) <= M) sq++;

        if (M != 0) {
            i64 hls = md(M, sq);
            if (hls != 1 && md(M, hls - 1) == sq) hls--;
            s = hls + sq;

            p = prime_enumerate(sq);
            ps = p.size();
            ans = T{};
        }
    }
    vector<T> pi_table() {
        if (M == 0) return {};
        i64 hls = md(M, sq);
        if (hls != 1 && md(M, hls - 1) == sq) hls--;

        vector<i64> hl(hls);
        for (i64 i = 1; i < hls; i++) hl[i] = md(M, i) - 1;

        vector<i64> hs(sq + 1);
        iota(begin(hs), end(hs), -1);

        i64 pi = 0;
        for (auto& x : p) {
            i64 x2 = i64(x) * x;
            i64 imax = min<i64>(hls, md(M, x2) + 1);
            for (i64 i = 1, ix = x; i < imax; ++i, ix += x) {
                hl[i] -= (ix < hls ? hl[ix] : hs[md(M, ix)]) - pi;
            }
            for (i64 n = sq; n >= x2; n--) hs[n] -= hs[md(n, x)] - pi;
            pi++;
        }

        vector<T> res;
        res.reserve(2 * sq + 10);
        for (auto& x : hl) res.push_back(x);
        for (i64 i = hs.size(); --i;) res.push_back(hs[i]);
        assert((i64)res.size() == s);
        return res;
    }

    i64 md(i64 n, i64 d) { return double(n) / d; }
    i64 idx(i64 n) { return n <= sq ? s - n : md(M, n); }
    void set_buf(vector<T>& _buf) { swap(buf, _buf); }
};
constexpr i64 N = 3e6;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    i64 n;
    cin >> n;

    auto prime = prime_enumerate(4e7);
    // auto brute = [&](i64 n) -> i64 {
    //     vector<i64> mp(n + 1);
    //     vector<i64> pq;
    //     for (auto p : prime) {
    //         if (p > n) break;
    //         for (auto q : prime) {
    //             if (q > n) break;
    //             if (p == q) continue;
    //             if (p * q > n) continue;
    //             mp[p * q] = 1;
    //             pq.push_back(p * q);
    //         }
    //     }
    //     for (i64 i = 0; i < pq.size(); i++)
    //         for (i64 j = 0; j < pq.size(); j++)
    //             if (pq[i] * pq[j] <= n) {
    //                 mp[pq[i] * pq[j]] = 1;
    //             }
    //     i64 ans = 0;
    //     for (i64 i = 1; i <= n; i++) ans += (mp[i] >= 1);
    //     return ans;
    // };
    // cerr << brute(n) << endl;
    vector<i64> mp(4e7, 0);
    vector<i64> pqn;
    for (auto p : prime) {
        mp[p] = 1;
        for (auto q : prime) {
            if (p * q >= N) break;
            if (p != q) pqn.push_back(p * q);
        }
    }
    sort(pqn.begin(), pqn.end());

    pqn.resize(unique(pqn.begin(), pqn.end()) - pqn.begin());

    for (i64 i = 1; i < 4e7; i++) {
        mp[i] = mp[i] + mp[i - 1];
    }
    mf_prefix_sum<i64> mf(n);
    auto pi = mf.pi_table();
    auto psolve = [&](i64 n, i64 p) -> i64 {
        if ((n / p) < N)
            return mp[n / p];
        else
            return pi[mf.idx(n / p)];
    };

    auto pqsolve = [&](i64 n) {
        i64 ans = 0;
        i64 q = 1;
        for (auto p : prime) {
            if (p * p > n) break;
            ans += psolve(n, p) - q;
            q++;
        }
        return ans;
    };
    i64 nn = pow(n, 0.75);
    map<i64, int> vis;
    i64 ans = 0;

    function<void(i64, i64, i64)> dfs = [&](i64 X, i64 Y, i64 Z) {
        cerr << X << " " << Y << " " << Z << endl;
        i64 x = prime[X], y = prime[Y], z = prime[Z];

        int now = !((x == y) || (y == z) || (x == z));

        if (!(x == y && y == z && z == x)) {
            if (!vis[x * y * z]) {
                ans +=
                    max(psolve(n, x * y * z) - psolve(max({x, y, z}), 1) + now,
                        0ll);
            }
        }
        vis[x * y * z] = 1;
        if (y * z * (prime[X + 1]) <= nn && !vis[y * z * (prime[X + 1])] &&
            X + 1 < prime.size())
            dfs(X + 1, Y, Z);
        if (x * z * (prime[Y + 1]) <= nn && !vis[x * z * (prime[Y + 1])] &&
            Y + 1 < prime.size())
            dfs(X, Y + 1, Z);
        if (x * y * (prime[Z + 1]) <= nn && !vis[x * y * (prime[Z + 1])] &&
            Z + 1 < prime.size())
            dfs(X, Y, Z + 1);
    };
    dfs(0, 0, 0);
    auto ppqqsolve = [&](i64 n) {
        i64 ans = 0;
        for (auto p : pqn) {
            if (p * p > n) break;
            ans++;
        }
        return ans;
    };
    cout << pqsolve(n) + ans + ppqqsolve(n);
}