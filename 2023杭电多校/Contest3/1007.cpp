#include <bits/stdc++.h>
using i64 = std::int64_t;

namespace Factor {
inline i64 binary_gcd(i64 a, i64 b) {
    if (a == 0 || b == 0) return a + b;
    char n = __builtin_ctzll(a);
    char m = __builtin_ctzll(b);
    a >>= n;
    b >>= m;
    n = std::min(n, m);
    while (a != b) {
        i64 d = a - b;
        char s = __builtin_ctzll(d);
        bool f = a > b;
        b = f ? b : a;
        a = (f ? d : -d) >> s;
    }
    return a << n;
}

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
    while (t++ % 40 || binary_gcd(prd, n) == 1) {
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

template <class T = u64>
std::vector<std::pair<T, int>> factorSortedList(u64 n) {
    // \prid x_i^p_i
    auto fac = factor(n);
    std::sort(fac.begin(), fac.end());

    std::vector<std::pair<T, int>> lt;
    for (int i = 0, j; i < int(fac.size()); i = j) {
        j = i;
        while (j < static_cast<int>(fac.size()) && fac[i] == fac[j]) j++;
        lt.emplace_back(fac[i], j - i);
    }

    return lt;
}
}  // namespace Factor

constexpr int P = 998244353;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        i64 x;
        std::cin >> x;
        if (x == 1) {
            std::cout << 1 << ' ';
            continue;
        }
        auto factor = Factor::factorSortedList(x);

        if (factor.size() >= 2) {
            std::cout << 1 << ' ';
        } else {
            std::cout << factor[0].first % P << ' ';
        }
    }
}