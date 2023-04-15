#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::tuple<i64, i64, i64>> vertex(n);
    std::vector<i64> v1, v2;
    for (auto& [x, y, val] : vertex) {
        std::cin >> x >> y >> val;
        v1.push_back(x);
        v2.push_back(y);
    }

    std::sort(begin(v1), end(v1));
    std::sort(begin(v2), end(v2));

    v1.resize(std::unique(begin(v1), end(v1)) - begin(v1));
    v2.resize(std::unique(begin(v2), end(v2)) - begin(v2));

    std::vector<std::pair<i64, int>> cntx(v1.size()), cnty(v2.size());

    for (const auto& [x, y, val] : vertex) {
        auto idx = std::lower_bound(begin(v1), end(v1), x) - begin(v1);
        auto idy = std::lower_bound(begin(v2), end(v2), y) - begin(v2);

        cntx[idx].first += val;
        cnty[idy].first += val;
        cntx[idx].second = idx;
        cnty[idy].second = idy;
    }

    i64 ans = 0;

    std::multiset<i64> se;
    std::vector<std::vector<i64>> id(v2.size());
    for (const auto& [x, y, val] : vertex) {
        auto idx = std::lower_bound(begin(v1), end(v1), x) - begin(v1);
        auto idy = std::lower_bound(begin(v2), end(v2), y) - begin(v2);

        ans = std::max(ans, cntx[idx].first + cnty[idy].first - val);
        id[cnty[idy].second].push_back(cntx[idx].first);
    }

    for (int i = 0; i < int(cntx.size()); i++) {
        se.insert(cntx[i].first);
    }
    for (int i = 0; i < int(cnty.size()); i++) {
        for (auto erax : id[i]) {
            auto pos = se.find(erax);
            se.erase(pos);
        }
        if (!se.empty()) ans = std::max(ans, cnty[i].first + *(se.rbegin()));
        for (auto erax : id[i]) {
            se.insert(erax);
        }
    }

    std::cout << ans << std::endl;

    return 0;
}