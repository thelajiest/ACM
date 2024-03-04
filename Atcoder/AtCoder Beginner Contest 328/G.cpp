#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::set<int>> cnt(n);
    for (int i = 0; i < n; i++) {
        int c;
        std::cin >> c;
        cnt[i].insert(c);
    }

    while (q--) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        if (cnt[a].size() > cnt[b].size()) {
            for (auto p : cnt[b]) cnt[a].insert(p);
            std::cout << cnt[a].size() << '\n';
            std::swap(cnt[a], cnt[b]);
        } else {
            for (auto p : cnt[a]) cnt[b].insert(p);
            std::cout << cnt[b].size() << '\n';
        }
        cnt[a].clear();
    }

    return 0;
}
