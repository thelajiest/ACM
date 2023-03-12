#include <bits/stdc++.h>

using i64 = std::int64_t;

namespace Factor {
using u64 = std::uint64_t;

u64 modmul(u64 a, u64 b, u64 M) {
    i64 ret = a * b - M * u64(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (i64)M);
}

u64 modpow(u64 b, u64 e, u64 mod) {
    u64 ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(u64 n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    std::vector<u64> A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    u64 s = __builtin_ctzll(n - 1), d = n >> s;
    for (u64 a : A) {  // ^ count trailing zeroes
        u64 p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}
u64 pollard(u64 n) {
    auto f = [n](u64 x, u64 k) { return modmul(x, x, n) + k; };
    u64 x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || std::gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x, i);
        if ((q = modmul(prd, std::max(x, y) - std::min(x, y), n))) prd = q;
        x = f(x, i), y = f(f(y, i), i);
    }
    return std::gcd(prd, n);
}
std::vector<u64> factor(u64 n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    u64 x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}
}  // namespace Factor

template <class T>
std::vector<T> OsakDivisorsFast(T x) {
    auto fac = Factor::factor(x);
    std::sort(fac.begin(), fac.end());
    std::vector<std::pair<T, int>> lt;
    for (int i = 0, j; i < int(fac.size()); i = j) {
        j = i;
        while (fac[j] == fac[i] && j < int(fac.size())) j++;
        lt.emplace_back(fac[i], j - i);
    }
    std::vector<T> div;
    auto dfs = [&](auto&& rec, int i, T c) {
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

std::unordered_map<i64, int> mp;
void solve() {
    i64 n;
    std::cin >> n;
    if (mp.count(n) > 0) {
        std::cout << mp[n] << '\n';
        return;
    }
    auto fac1 = OsakDivisorsFast(n);
    auto fac2 = OsakDivisorsFast(n - 1);
    int ans = 0;
    auto check = [&](i64 x, i64 b) -> bool {
        while (x) {
            if (x % b != 0 && x % b != 1) return false;
            x /= b;
        }
        return true;
    };

    std::copy(begin(fac2), end(fac2), std::back_inserter(fac1));
    std::sort(begin(fac1), end(fac1));
    fac1.resize(std::unique(begin(fac1), end(fac1)) - begin(fac1));
    for (auto p : fac1) {
        if (p >= 2 && check(n, p)) ans++;
    }
    std::cout << ans << '\n';
    mp[n] = ans;

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