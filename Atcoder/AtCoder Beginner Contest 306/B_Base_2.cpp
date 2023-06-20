#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr int n = 64;

    std::uint64_t ans = 0;
    for (uint64_t i = 0; i < 64; i++) {
        int x;
        std::cin >> x;
        if (x == 1) ans |= (1UL << i);
    }

    std::cout << ans << std::endl;

    return 0;
}