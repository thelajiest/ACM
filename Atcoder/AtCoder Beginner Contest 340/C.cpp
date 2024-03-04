#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N;
    std::cin >> N;
    std::map<i64, i64> sum;
    auto dfs = [&](auto&& self, i64 now) -> i64 {
        if (sum.count(now)) return sum[now];
        i64 ans = now;
        i64 low = now / 2;
        i64 high = (now + 1) / 2;
        if (low >= 2 && high == low) ans += 2 * self(self, low);
        if (low >= 2 && high != low) ans += self(self, high) + self(self, low);
        if (low == 1 && high != 1) ans += self(self, high);

        return sum[now] = ans;
    };

    std::cout << dfs(dfs, N) << std::endl;

    return 0;
}