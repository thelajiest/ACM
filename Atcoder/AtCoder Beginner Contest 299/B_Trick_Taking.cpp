#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, T;

    std::cin >> n >> T;

    std::vector<int> c(n), r(n);

    for (int i = 0; i < n; i++) std::cin >> c[i];
    for (int i = 0; i < n; i++) std::cin >> r[i];

    std::vector<std::pair<int, int>> colT, colF;

    for (int i = 0; i < n; i++) {
        if (c[i] == T) colT.emplace_back(r[i], i);
        if (c[i] == c[0]) colF.emplace_back(r[i], i);
    }

    if (!colT.empty()) {
        std::sort(begin(colT), end(colT), std::greater());
        std::cout << colT[0].second + 1;
    } else {
        std::sort(begin(colF), end(colF), std::greater());
        std::cout << colF[0].second + 1;
    }

    return 0;
}
