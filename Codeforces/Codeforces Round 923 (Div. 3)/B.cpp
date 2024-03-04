#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> vis(n);
    std::vector<char> ans(n);
    for (int k = 0; k < 26; k++) {
        int now = 0;
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            if (a[i] == now) {
                now += 1;
                vis[i] = 1;
                ans[i] = char(k + 'a');
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i];
    }
    std::cout << '\n';

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