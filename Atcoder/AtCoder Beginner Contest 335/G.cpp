#include <bits/stdc++.h>
using i64 = std::int64_t;
using i128 = __int128_t;

i64 power(i64 a, i64 b, i64 p) {
    i128 ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = (i128)a * a % p;
        b >>= 1;
    }

    return (i64)(ret % p);
}
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    i64 P;
    std::cin >> N >> P;

    auto div = Factor::factor(P - 1);

    std::vector<i64> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::unordered_map<i64, i64> cnt;
    for (int i = 0; i < N; i++) {
        i64 cur = P - 1;
        for (auto m : div) {
            if (power(A[i], cur / m, P) == 1) {
                cur /= m;
            }
        }
        cnt[cur]++;
    }

    i64 ans = 0;
    for (auto [k1, num1] : cnt) {
        for (auto [k2, num2] : cnt) {
            ans += (k1 % k2 == 0) ? num1 * num2 : 0;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
