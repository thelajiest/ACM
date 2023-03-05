#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> div(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) div[j]++;
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1LL * div[i] * div[n - i];
    }

    std::cout << ans << std::endl;

    return 0;
}