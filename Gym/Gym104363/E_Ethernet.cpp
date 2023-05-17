#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::cout << std::fixed << std::setprecision(10);
    if (n != m)
        std::cout << 1.0 / (m + 1) << std::endl;
    else
        std::cout << 1.0 / m << std::endl;
    return 0;
}