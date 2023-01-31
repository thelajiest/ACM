#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;
    std::map<int, int> mp;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        mp[x]++;
    }

    int ans = 0;
    while (mp.size() > 0) {
        int frt = -1;

        for (auto it = mp.begin(); it != mp.end();) {
            auto& [x, cnt] = *it;
            if (x != frt + 1 && frt != -1) break;
            frt = x;
            cnt--;
            if (cnt == 0)
                it = mp.erase(it);
            else
                it++;
        }

        ans++;
    }

    std::cout << ans << '\n';

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