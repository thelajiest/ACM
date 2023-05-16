#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> a;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (i == 0) {
            a.push_back(x);
        } else {
            int last = a.back();
            if (std::abs(last - x) == 1) {
                a.push_back(x);
                continue;
            }

            if (last > x) {
                for (int j = last - 1; j >= x + 1; j--) {
                    a.push_back(j);
                }

            } else {
                for (int j = last + 1; j <= x - 1; j++) {
                    a.push_back(j);
                }
            }
            a.push_back(x);
        }
    }

    for (auto p : a) std::cout << p << " ";

    return 0;
}