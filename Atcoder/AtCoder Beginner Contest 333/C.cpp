#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    for (int d = 1; d <= 12; d++) {
        for (int a = d - 1; a >= 0; a--) {
            for (int b = d - a - 1; b >= 0; b--) {
                int c = d - a - b;
                if (--N == 0) {
                    std::cout << std::string(a, '1') + std::string(b, '2') +
                                     std::string(c, '3')
                              << std::endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}