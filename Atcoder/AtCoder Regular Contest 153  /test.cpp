#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> a(n);

    for (auto& cur : a) std::cin >> cur;
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0)
            ans += a[i];
        else {
            ans += 1LL * i * a[i];
        }
    }

    std::cout << ans << std::endl;
    return 0;
}