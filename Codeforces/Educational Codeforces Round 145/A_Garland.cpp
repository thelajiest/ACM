#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    std::string s;
    std::cin >> s;

    std::vector<int> cnt(10);
    for (auto p : s) cnt[p - '0']++;

    std::vector<int> d;
    for (auto p : cnt)
        if (p != 0) d.push_back(p);

    std::sort(begin(d), end(d));

    std::sort(begin(s), end(s));
    s.resize(std::unique(begin(s), end(s)) - begin(s));

    if (s.size() == 1) {
        std::cout << -1 << '\n';
    } else {
        if ((s.size() == 2) && (d[0] == 1))
            std::cout << 6 << '\n';
        else
            std::cout << 4 << '\n';
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}