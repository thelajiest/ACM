#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, M;

    std::cin >> n >> M;

    std::vector<int> p(n + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i++) p[i] = 1LL * p[i - 1] * n % M;

    int ans = 0;
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        ans =
            (ans + 1LL * cnt * p[n - i] % M * (1LL * i * (i - 1) / 2 % M) % M) %
            M;
        cnt = 1LL * cnt * (n - i) % M;
    }

    ans = 1LL * ans * n % M;

    std::cout << ans << std::endl;

    return 0;
}