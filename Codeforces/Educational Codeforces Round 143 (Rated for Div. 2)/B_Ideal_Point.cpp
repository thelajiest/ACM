#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<std::pair<int, int>>> cnt(51);

    for (int i = 1; i <= n; i++) {
        int l, r;
        std::cin >> l >> r;
        for (int j = l; j <= r; j++) {
            cnt[j].push_back({l, r});
        }
    }

    int kans = cnt[k].size();

    bool flag = true;
    for (int i = 1; i <= 50; i++) {
        if (i == k || cnt[i].size() < kans) continue;
        int need = cnt[i].size() - kans + 1;
        for (auto [l, r] : cnt[i]) {
            if (l <= k && k <= r) continue;
            need--;
        }
        if (need > 0) {
            flag = false;
        }
    }

    if (flag)
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