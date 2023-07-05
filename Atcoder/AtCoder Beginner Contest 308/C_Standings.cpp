#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::tuple<int, int, int>> a(n);

    for (int i = 0; i < n; i++) {
        auto& [A, B, id] = a[i];
        std::cin >> A >> B;
        id = i;
    }

    std::sort(begin(a), end(a), [&](const auto& ca, const auto& cb) {
        auto [A1, B1, i1] = ca;
        auto [A2, B2, i2] = cb;
        B1 += A1;
        B2 += A2;
        if (1LL * A1 * B2 > 1LL * A2 * B1) return true;
        if (1LL * A1 * B2 < 1LL * A2 * B1) return false;
        return i1 < i2;
    });

    for (auto [A, B, id] : a) {
        std::cout << id + 1 << " ";
    }

    return 0;
}