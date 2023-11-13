#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 p, k, t;

    std::cin >> p >> k >> t;

    i64 a = p - k;

    i64 ans = 1;
    while (t) {
        if (t % 2 == 1) ans = ans * a % p;
        a = a * a % p;
        t /= 2;
    }

    std::cout << ans << std::endl;

    return 0;
}