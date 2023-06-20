#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n + 1);

    for (int i = 1; i <= 3 * n; i++) {
        int x;
        std::cin >> x;
        a[x].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        std::sort(begin(a[i]), end(a[i]));
        a[i].push_back(i);
    }

    std::sort(begin(a) + 1, end(a),
              [&](auto A, auto B) { return A[1] < B[1]; });

    for (int i = 1; i <= n; i++) {
        std::cout << a[i][3] << " ";
    }
    return 0;
}