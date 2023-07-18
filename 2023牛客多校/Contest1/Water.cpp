#include <bits/stdc++.h>

using i64 = std::int64_t;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto res = exgcd(b, a % b, x, y);
    i64 t = x;
    x = y;
    y = t - a / b * y;
    return res;
}

template <class T>
T abs(T x) {
    if (x < 0) return -x;
    return x;
}
void solve() {
    i64 A, B, C;
    std::cin >> A >> B >> C;

    i64 x, y;
    i64 gcd = std::gcd(A, B);
    if (C % gcd != 0) {
        std::cout << -1 << '\n';
        return;
    }

    exgcd(A / gcd, B / gcd, x, y);
    i64 d = gcd;
    /*
        x0 = C/d * x + B/d * k
        y0 = C/d * y - A/d * k

    */

    i64 x0 = (C / d) * x;
    i64 y0 = (C / d) * y;

    i64 ans = std::numeric_limits<i64>::max();

    i64 k1 = (-(C / d * x)) / (B / d);

    for (i64 k0 = k1 - 1000; k0 <= k1 + 1000; k0++) {
        i64 x1 = x0 + k0 * (B / d);
        i64 y1 = y0 - k0 * (A / d);
        if ((x1 < 0 && y1 > 0) || (x1 > 0 && y1 < 0)) {
            ans = std::min(ans, 2 * (abs<i64>(x1) + abs<i64>(y1)) - 1);
        } else {
            ans = std::min(ans, 2 * (x1 + y1));
        }
    }

    i64 k2 = ((C / d) * y) / (A / d);
    for (i64 k0 = k2 - 1000; k0 <= k2 + 1000; k0++) {
        i64 x1 = x0 + k0 * (B / d);
        i64 y1 = y0 - k0 * (A / d);
        if ((x1 < 0 && y1 > 0) || (x1 > 0 && y1 < 0)) {
            ans = std::min(ans, 2 * (abs<i64>(x1) + abs<i64>(y1)) - 1);
        } else {
            ans = std::min(ans, 2 * (x1 + y1));
        }
    }
    std::cout << ans << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}