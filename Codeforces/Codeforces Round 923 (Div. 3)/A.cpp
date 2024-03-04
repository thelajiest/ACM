#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int left = -1, right = -2;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            left = i;
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'B') {
            right = i;
            break;
        }
    }

    if (left > right) {
        std::cout << 0 << '\n';
    } else {
        std::cout << right - left + 1 << '\n';
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