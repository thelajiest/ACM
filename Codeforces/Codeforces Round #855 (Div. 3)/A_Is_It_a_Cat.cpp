#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    for (auto& c : s) {
        if (std::islower(c)) c = c - 'a' + 'A';
    }

    std::string ans;
    for (int i = 0, j; i < n; i = j) {
        j = i;
        while (j < n && s[j] == s[i]) j++;
        ans += s[i];
    }

    if (ans == "MEOW")
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