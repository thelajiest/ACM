#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> ans(n, std::vector<char>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            std::cin >> x;
            if (x == 0)
                ans[i][j] = '.';
            else
                ans[i][j] = char('A' + x - 1);
        }
    }

    for (auto p : ans) {
        for (auto q : p) std::cout << q;
        std::cout << '\n';
    }

    return 0;
}