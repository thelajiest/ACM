#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 a, b;

    std::string _;
    std::cin >> _;
    a = std::stoll(_, 0, 2);
    std::cin >> _;
    b = std::stoll(_, 0, 2);

    if (a == 0 && b == 0) {
        std::cout << 0;
        return 0;
    }
    if (a == 0 && b != 0) {
        std::cout << -1;
        return 0;
    }

    std::cout << std::abs(a - b);
    return 0;
}