#include <bits/stdc++.h>

using i64 = std::int64_t;

std::string DNA = "ATGC";
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    int n = s.size();

    int q;
    std::cin >> q;

    std::vector<std::array<int, 4>> d(n);

    d[0][0] = (s[0] == 'A');
    d[0][1] = (s[0] == 'T');
    d[0][2] = (s[0] == 'G');
    d[0][3] = (s[0] == 'C');

    for (int i = 0; i + 1 < n; i++) {
        d[i + 1][0] = d[i][0] + (s[i + 1] == 'A');
        d[i + 1][1] = d[i][1] + (s[i + 1] == 'T');
        d[i + 1][2] = d[i][2] + (s[i + 1] == 'G');
        d[i + 1][3] = d[i][3] + (s[i + 1] == 'C');
    }

    auto get = [&](int l, int r, int type) -> int {
        if (l == 0) return d[r][type];
        return d[r][type] - d[l - 1][type];
    };
    while (q--) {
        int s, e;
        std::cin >> s >> e;
        s--, e--;
        std::vector<std::pair<int, int>> order;
        for (int i = 0; i < 4; i++) {
            order.emplace_back(get(s, e, i), i);
        }
        std::sort(begin(order), end(order), [&](auto a, auto b) {
            if (a.first > b.first) return true;
            if (a.first < b.first) return false;
            return a.second < b.second;
        });

        for (int i = 0; i < 4; i++) {
            auto c = order[i].second;
            std::cout << DNA[c];
        }

        std::cout << '\n';
    }

    return 0;
}