#include <bits/stdc++.h>

using i64 = std::int64_t;

constexpr double EPS = 1E-10;
const double PI = acos(-1);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double a, b;
    std::cin >> a >> b;

    double lo = 0, hi = 1E4;

    while (fabs(hi - lo) > EPS) {
        double m = (hi + lo) / 2.0;
        double h = (m <= b) ? 0 : acos(b / m);
        if (h <= PI / 6.0 && m * cos(PI / 6 - h) <= a)
            lo = m;
        else
            hi = m;
    }

    std::cout << std::fixed << std::setprecision(10) << lo;

    return 0;
}