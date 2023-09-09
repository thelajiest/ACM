#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    i64 ans = 1E18;
    for (int i = 0; i < n; i++) {
        i64 x;
        std::cin >> x;
        ans = std::min(ans, abs(x));
    }

    std::cout << ans << std::endl;
    return 0;
}