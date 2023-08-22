#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n);
    std::vector<int> b;
    for (int i = 0, x, y; i < n; i++) {
        std::cin >> x >> y;
        a[x - 1].push_back(y);
    }

    for (int i = 0; i < n; i++)
        std::sort(begin(a[i]), end(a[i]), std::greater());

    int ans = 0;
    for (auto p : a) {
        if (p.size() >= 2) ans = std::max(ans, p[0] + p[1] / 2);
        if (p.size() >= 1) b.push_back(p[0]);
    }
    std::sort(begin(b), end(b), std::greater());

    std::cout << std::max(b[0] + b[1], ans);

    return 0;
}