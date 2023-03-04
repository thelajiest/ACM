#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<std::array<int, 2>> cnt(26);

    for (auto c : s)
        if (std::islower(c))
            ++cnt[c - 'a'][0];
        else
            ++cnt[c - 'A'][1];
    int ans = 0;

    for (auto &[l, u] : cnt) {
        ans += std::min(l, u);
        int d = std::min(abs(l - u) / 2, k);
        k -= d;
        ans += d;
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