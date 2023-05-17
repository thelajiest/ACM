#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr int P = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k;
    std::cin >> k;

    int ans = 1;

    for (int i = 0; i < k - 1; i++) ans = 1LL * ans * 2 % P;

    std::cout << ans << std::endl;

    return 0;
}