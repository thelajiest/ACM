#include <bits/stdc++.h>
using i64 = std::int64_t;
using i128 = __int128_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 B;

    std::cin >> B;

    for (i64 i = 1; i < 18; i++) {
        i128 cur = 1;
        for (int j = 0; j < i; j++) {
            cur *= (i128)i;
        }

        if (cur == B) {
            std::cout << i << std::endl;
            return 0;
        }
    }

    std::cout << "-1" << std::endl;

    return 0;
}