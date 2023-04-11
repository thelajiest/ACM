#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 a, b;

    std::cin >> a >> b;

    i64 t = 0;
    while (a != b) {
        if (a < b) std::swap(a, b);
        if (a > b) {
            i64 k = (a + b - 1) / b - 1;
            a = a - k * b;
            t += k;
        }
    }

    std::cout << t << std::endl;

    return 0;
}