#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    int last = 0;
    int now = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> now;
        if (i >= 1 && now - last <= k) {
            std::cout << now;
            return 0;
        }
        last = now;
    }

    std::cout << -1;

    return 0;
}