#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N, X;
    std::cin >> N >> X;

    std::unordered_map<i64, i64> mp;
    mp.clear();

    for (int i = 0; i < N; i++) {
        i64 x;
        std::cin >> x;
        mp[x]++;
    }

    for (auto [val, _] : mp) {
        if (mp.count(val + X) > 0) {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }

    std::cout << "No" << std::endl;

    return 0;
}
