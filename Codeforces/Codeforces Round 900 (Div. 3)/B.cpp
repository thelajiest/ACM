#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> ans;

    for (int i = 0; i < n; i++) {
        ans.push_back(3 * i + 2);
    }

    for (int i = 0; i + 2 < n; i++) {
        assert((3 * ans[i + 2] % (ans[i] + ans[i + 1])) != 0);
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
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