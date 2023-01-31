#include <bits/stdc++.h>

using i64 = std::int64_t;

const std::string pi = "314159265358979323846264338327";
void solve() {
    std::string s;
    std::cin >> s;

    int ans = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == pi[i])
            ans++;
        else
            break;
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