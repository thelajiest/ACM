#include <bits/stdc++.h>
using i64 = std::int64_t;

constexpr int N = 500;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adx(n, std::vector<int>(n));
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adx[x][y] += 1;
        adx[y][x] += 1;
    }

    int odd(0), even(0);
    for (int i = 0; i < (1 << n); i++) {
        std::vector<int> node;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) node.push_back(j);
        }
        int cur = 0;
        for (auto x : node) {
            for (auto y : node) {
                if (x != y) cur += adx[x][y];
            }
        }
        cur /= 2;
        if (cur & 1)
            odd++;
        else
            even++;
    }

    std::cout << "odd :=" << odd << std::endl;
    std::cout << "even :=" << even << std::endl;
    return 0;
}