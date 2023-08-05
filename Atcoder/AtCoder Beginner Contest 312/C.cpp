#include <bits/stdc++.h>
using i64 = std::int64_t;

i64 solve(int n) {
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans += std::gcd((1 << i) - 1, (1 << j) - 1);
        }
    }
    return ans;
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int n = 1; n < 120; n++) {
        std::cout << n << ": " << (1 << (n + 1)) << " " << solve(n) << " "
                  << std::endl;
    }

    return 0;
}