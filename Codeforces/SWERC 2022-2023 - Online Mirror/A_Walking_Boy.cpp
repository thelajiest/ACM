#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a;
    a.push_back(0);

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.push_back(x);
    }

    a.push_back(1440);

    int cnt = 0;
    for (int i = 0; i < int(a.size()) - 1; i++) {
        int step = (a[i + 1] - a[i]) / 120;
        cnt += step;
    }

    if (cnt >= 2)
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

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