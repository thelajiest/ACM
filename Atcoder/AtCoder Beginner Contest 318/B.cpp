#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector vis(101, std::vector(101, 0));

    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        b--, d--;
        for (int x = a; x <= b; x++)
            for (int y = c; y <= d; y++) vis[x][y] = 1;
    }
    int ans = 0;
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++) ans += vis[i][j];

    std::cout << ans << std::endl;
    return 0;
}