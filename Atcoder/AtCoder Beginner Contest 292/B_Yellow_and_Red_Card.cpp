#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> a(n);

    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++) {
        int op, x;
        std::cin >> op >> x;
        x--;
        if (op == 1) {
            a[x].first++;
        }
        if (op == 2) {
            a[x].second++;
        }
        if (op == 3) {
            if (a[x].first >= 2 || a[x].second >= 1)
                std::cout << "Yes\n";
            else
                std::cout << "No\n";
        }
    }

    return 0;
}