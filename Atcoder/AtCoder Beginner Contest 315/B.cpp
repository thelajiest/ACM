#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> m;

    std::vector<int> D(m);
    for (auto& v : D) std::cin >> v;

    int mid = (std::accumulate(begin(D), end(D), 0) + 1) / 2;

    int a, b = mid;
    for (int i = 0; i < m; i++) {
        if (b - D[i] <= 0) {
            a = i;
            break;
        }
        b -= D[i];
    }

    std::cout << a + 1 << " " << b << std::endl;
    return 0;
}