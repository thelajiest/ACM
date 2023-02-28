#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> need;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1]) need.push_back(i);
    }

    bool flag = false;
    for (int i = 1; i < need.size(); i++)
        if (need[i] - need[i - 1] > 1) {
            std::cout << "No\n";
            return;
        }
    std::cout << "Yes\n";
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