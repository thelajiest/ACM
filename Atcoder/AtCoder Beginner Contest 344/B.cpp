#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> a;

    int x;
    while (std::cin >> x) {
        a.push_back(x);
    }

    for (auto it = a.rbegin(); it != a.rend(); it++) {
        std::cout << (*it) << '\n';
    }

    return 0;
}