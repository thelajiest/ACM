#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    for (int i = 0; i < 2 * N + 1; i++) {
        if (i & 1) {
            std::cout << 0;
        } else {
            std::cout << 1;
        }
    }

    return 0;
}