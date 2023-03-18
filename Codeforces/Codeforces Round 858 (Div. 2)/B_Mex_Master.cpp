#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    int cnt = 0;
    int cnt1 = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x == 0) cnt++;
        if (x == 1) cnt1++;
    }
    if (cnt <= (n + 1) / 2)
        std::cout << 0 << '\n';
    else {
        if (cnt + cnt1 == n && cnt1 >= 1)
            std::cout << 2 << '\n';
        else
            std::cout << 1 << '\n';
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