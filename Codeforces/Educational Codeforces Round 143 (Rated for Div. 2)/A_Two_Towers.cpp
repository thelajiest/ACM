#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::string a, b;
    std::cin >> a >> b;
    std::reverse_copy(b.begin(), b.end(), std::back_inserter(a));

    int change = 0;
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] == a[i + 1]) change++;
    }

    if (change <= 1) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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