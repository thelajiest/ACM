#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    freopen("lock.in", "r", stdin);
    freopen("lock.out", "w", stdout);
    int n;
    std::cin >> n;

    std::vector<std::array<int, 5>> mask(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            std::cin >> mask[i][j];
        }
    }

    std::array<int, 5> d;
    int ans = 0;
    for (int i = 0; i < 100000; i++) {
        for (int j = 0, base = 1; j < 5; j++, base *= 10) {
            d[j] = (i / base) % 10;
        }
        auto check1 = [&](const std::array<int, 5>& a,
                          const std::array<int, 5>& b) {
            int cnt = 0;
            for (int k = 0; k < 5; k++) cnt += (a[k] == b[k]);
            return (cnt == 4);
        };

        auto check2 = [&](const std::array<int, 5>& a,
                          const std::array<int, 5>& b) {
            std::vector<std::pair<int, int>> diff;
            for (int k = 0; k < 5; k++)
                if (a[k] != b[k]) diff.emplace_back((a[k] - b[k] + 10) % 10, k);
            if ((int)diff.size() != 2) return false;
            return (diff[0].first == diff[1].first) &&
                   (diff[1].second - diff[0].second == 1);
        };

        bool flag = true;
        for (int j = 0; j < n; j++) {
            if ((!check1(d, mask[j])) && (!check2(d, mask[j]))) flag = false;
        }

        if (flag) {
            ans++;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}