#include <bits/stdc++.h>

using i64 = std::int64_t;
std::mt19937_64 rng(std::time(0));

i64 power(i64 a, i64 b, i64 p) {
    i64 ret = 1;
    for (; b != 0; a = 1LL * a * a % p, b /= 2) {
        if (b % 2 == 1) ret = 1LL * ret * a % p;
    }
    return ret;
}

void solve() {
    i64 n, p;
    std::cin >> n >> p;
    for (;;) {
        auto rd = std::uniform_int_distribution<i64>(1, p - 1);
        i64 a = rd(rng);
        i64 b = rd(rng);
        while (b == a) b = rd(rng);
        i64 c = rd(rng);
        while (c == b || c == a) c = rd(rng);
        auto F = [&p, &n](i64 a, i64 b, i64 c) -> i64 {
            i64 ret1 = (a + b + c) % p;
            i64 ret2 =
                ((power(a, n, p) + power(b, n, p)) % p + power(c, n, p)) % p;
            i64 ret3 = ((power(a, 2 * n, p) + power(b, 2 * n, p)) % p +
                        power(c, 2 * n, p)) %
                       p;
            return (ret1 * ret2 % p * ret3) % p;
        };
        auto G = [&p, &n](i64 a, i64 b, i64 c) -> i64 {
            return ((power(a, 3 * n, p) + power(b, 3 * n, p)) % p +
                    power(c, 3 * n, p)) %
                   p;
        };
        auto g = G(a, b, c);
        auto f = F(a, b, c);
        if (g != 0 && f != 0) {
            i64 t = power(f, p - 2, p) * g % p;
            std::vector<i64> ans = {t * a % p, t * b % p, t * c % p};
            std::sort(begin(ans), end(ans));

            assert(F(ans[0], ans[1], ans[2]) == G(ans[0], ans[1], ans[2]));

            for (auto it : ans) {
                std::cout << it << " \n"[it == ans.back()];
            }
            break;
        }
    }

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