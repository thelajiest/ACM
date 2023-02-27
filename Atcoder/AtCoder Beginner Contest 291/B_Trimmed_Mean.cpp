#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> s(5 * n);
    for (auto& it : s) std::cin >> it;

    std::sort(s.begin(), s.end());
    double sum = std::accumulate(s.begin() + n, s.begin() + 4 * n, 0.0);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << sum / (3.0 * n);

    return 0;
}