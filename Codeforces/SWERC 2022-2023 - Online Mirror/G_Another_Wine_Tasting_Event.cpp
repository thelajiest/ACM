#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> d(2 * n);

    for (int i = 0; i < 2 * n - 1; i++) {
        d[i + 1] = d[i] + (s[i] == 'W');
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans = std::max(ans, d[i + n] - d[i]);
    }

    std::cout << ans << std::endl;

    return 0;
}