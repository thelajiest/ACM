#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int A, B, D;
    std::cin >> A >> B >> D;

    for (int i = A; i <= B; i += D) {
        std::cout << i << " ";
    }

    return 0;
}