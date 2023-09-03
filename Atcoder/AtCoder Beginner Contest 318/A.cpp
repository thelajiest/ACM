#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, p;
    std::cin >> n >> m >> p;
    int ans = 0;
    for (int i = m; i <= n; i += p) ans++;
    std::cout << ans << std::endl;

    return 0;
}