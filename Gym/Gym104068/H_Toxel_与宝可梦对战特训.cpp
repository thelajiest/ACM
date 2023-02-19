#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::sort(begin(a), end(a));

    i64 ans = 0;
    if (n % 2 == 0) {
        for (int i = 0; i < n; i++) {
            ans = std::max(ans, 1LL * a[i] * a[n - i - 1]);
        }
        std::cout << ans << std::endl;
    } else {
        for (int i = 0; i < n; i++) {
            if (i == (n - 1) / 2 - 1 || i == (n - 1) / 2 ||
                i == (n - 1) / 2 + 1)
                continue;
            ans = std::max(ans, 1LL * a[i] * a[n - i - 1]);
        }
        ans = std::max(ans, 1LL * a[(n - 1) / 2 - 1] * a[(n - 1) / 2]);
        ans = std::max(ans, 1LL * a[(n - 1) / 2] * a[(n - 1) / 2 + 1]);

        ans = std::max(ans, 1LL * a[(n - 1) / 2 + 1] * a[(n - 1) / 2 - 1]);
        std::cout << ans << std::endl;
    }
    return 0;
}