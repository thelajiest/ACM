#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int ans = n - 1;

    for (int i = 2; i < n; i++) ans -= (s[i - 2] == s[i]);

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