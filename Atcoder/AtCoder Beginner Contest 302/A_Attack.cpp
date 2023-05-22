#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 a, b;

    std::cin >> a >> b;

    std::cout << (a + b - 1) / b << std::endl;

    return 0;
}