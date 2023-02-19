#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double x, y;
    std::cin >> x >> y;

    std::cout << std::fixed << std::setprecision(10) << x / (y + 1)
              << std::endl;
    return 0;
}