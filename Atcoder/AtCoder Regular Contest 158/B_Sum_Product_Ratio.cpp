#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    auto f = [&](int x, int y, int z) -> double {
        double up = 1.0 * x + 1.0 * y + 1.0 * z;
        double down = 1.0 * x * y * z;
        return up / down;
    };
    if (n < 6) {
        double max = -std::numeric_limits<double>::max();
        double min = std::numeric_limits<double>::max();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++) {
                    max = std::max(max, f(a[i], a[j], a[k]));
                    min = std::min(min, f(a[i], a[j], a[k]));
                }
        std::cout << std::fixed << std::setprecision(15) << min << std::endl
                  << max << std::endl;
    } else {
        std::sort(begin(a), end(a));
        std::vector<int> need;
        int zero = std::lower_bound(a.begin(), a.end(), 0) - a.begin();
        for (int i = 0; i < zero; i++) {
            if (i < 3 || zero - i <= 3) need.push_back(a[i]);
        }
        for (int i = zero; i < n; i++) {
            if (i - zero < 3 || n - i <= 3) need.push_back(a[i]);
        }

        double max = -std::numeric_limits<double>::max();
        double min = std::numeric_limits<double>::max();
        int sz = need.size();
        for (int i = 0; i < sz; i++)
            for (int j = i + 1; j < sz; j++)
                for (int k = j + 1; k < sz; k++) {
                    max = std::max(max, f(need[i], need[j], need[k]));
                    min = std::min(min, f(need[i], need[j], need[k]));
                }
        std::cout << std::fixed << std::setprecision(15) << min << std::endl
                  << max << std::endl;
    }
    return 0;
}