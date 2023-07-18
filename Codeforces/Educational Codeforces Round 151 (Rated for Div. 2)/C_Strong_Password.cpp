#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    std::string s;
    std::cin >> s;

    int m;
    std::cin >> m;

    std::string l, r;
    std::cin >> l >> r;

    int pos = 0;

    for (int i = 0; i < m; i++) {
        int maxPos = -1;
        for (char t = l[i]; t <= r[i]; t++) {
            int p = pos;
            while (p < (int)s.size() && s[p] != t) {
                ++p;
            }
            maxPos = std::max(maxPos, p);
        }
        pos = maxPos + 1;
    }

    if (pos > (int)s.size()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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