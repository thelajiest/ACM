#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double  x, y, r;
    std::cin >> x >> y >> r;

    i64 ans = 0;
    for (i64 i = ceil(x - r); i <= floor(x + r); i++) {
        i64 y1 = floor(y + sqrtl(r * r - (i - x) * (i - x)));
        i64 y2 = ceil(y - sqrtl(r * r - (i - x) * (i - x)));
        ans += y1 - y2 + 1;
    }

    std::cout << ans << std::endl;

    return 0;
}