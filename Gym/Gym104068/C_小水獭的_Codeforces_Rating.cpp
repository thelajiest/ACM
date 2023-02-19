#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, r;
    std::cin >> n >> r;

    std::vector<i64> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }

    for (int i = 0; i < n; i++) {
        auto f = [](i64 r, i64 s) -> i64 {
            return r + ceil((double)(s - r) / 4.0);
        };
        if (f(r, s[i]) < r) r = f(r, s[i]);
    }

    std::cout << r << std::endl;

    return 0;
}