#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    std::vector<std::vector<int>> b(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) std::cin >> a[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) std::cin >> b[i][j];
    }

    bool ok = false;
    for (int k = 0; k < 4; k++) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == 0) continue;
                if (b[i][j] != 1) flag = false;
            }
        }

        std::vector<std::vector<int>> b2(n, std::vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) b2[i][j] = b[n - j - 1][i];
        }
        b = b2;
        ok |= flag;
    }
    if (ok)
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;
}