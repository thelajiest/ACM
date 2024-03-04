#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> d(n);

    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int m = i + 1;
        bool flag = true;
        int p = m;
        while (p) {
            if (p % 10 != m % 10) flag = false;
            p /= 10;
        }
        if (!flag) continue;
        for (int j = 1; j <= d[i]; j++) {
            int ok = 1;
            int p = j;
            while (p) {
                if (p % 10 != m % 10) ok = 0;
                p /= 10;
            }
            ans += ok;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}