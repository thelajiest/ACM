#include <bits/stdc++.h>

using i64 = std::int64_t;

template <typename T>
constexpr T safe_mod(T x, T m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
template <typename T>
constexpr std::pair<T, T> inv_gcd(T a, T b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    T s = b, t = a;
    T m0 = 0, m1 = 1;
    while (t) {
        T u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

template <typename T>
T inv_mod(T x, T m) {
    assert(1 <= m);
    auto z = inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

template <typename T>
std::pair<T, T> crt(const std::vector<T>& r, const std::vector<T>& m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    T r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        T r1 = safe_mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        auto [g, im] = inv_gcd(m0, m1);
        T u1 = (m1 / g);
        if ((r1 - r0) % g) return {0, 0};
        T x = (r1 - r0) / g % u1 * im % u1;
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> p = {4, 5, 7, 9, 11, 13, 17, 19, 23};

    int M = 108;

    std::cout << M << std::endl;
    std::cout.flush();

    std::vector<int> to(M + 1);
    int np = 1;
    for (int i = 0; i < static_cast<int>(p.size()); i++) {
        int cur = p[i];
        int fn = np;
        for (int j = 1; j <= cur; j++) {
            if (j != cur)
                to[np] = j + fn;
            else
                to[np] = fn;
            np++;
        }
    }

    for (int i = 1; i <= M; i++) {
        std::cout << to[i] << " ";
    }
    std::cout << std::endl;
    std::cout.flush();

    std::vector<int> ans(M + 1);
    for (int i = 1; i <= M; i++) {
        std::cin >> ans[i];
    }

    std::vector<int> res;

    for (int i = 0, fs = 1; i < static_cast<int>(p.size()); i++) {
        int diff = ((ans[fs] - fs) % p[i] + p[i]) % p[i];
        res.push_back(diff);
        fs += p[i];
    }

    auto [rem, mod] = crt<int>(res, p);

    std::cout << rem << std::endl;

    return 0;
}