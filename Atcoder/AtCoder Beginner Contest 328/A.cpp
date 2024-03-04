#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;
    i64 ans = 0;

    for (int i = 0; i < n; i++) {
        i64 now{};
        std::cin >> now;
        if (now <= x) ans += now;
    }

    std::cout << ans << std::endl;

    return 0;
}